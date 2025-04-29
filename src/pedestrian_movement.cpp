#include "utils.h"

int conflictMatrix[DIM+1][DIM+1];
int rowsMatrix[9][DIM+1][DIM+1];
int collumnsMatrix[9][DIM+1][DIM+1];
vector<vpi>posMov(DIM+1, vpi(DIM+1, {0, 0}));

void initializeConflicts(){
    memset(conflictMatrix, 0, sizeof(conflictMatrix));
    memset(rowsMatrix, 0, sizeof(rowsMatrix));
    memset(collumnsMatrix, 0, sizeof(collumnsMatrix));
}

void defineParkArea(vector<vb>&parkArea, ifstream &infilePark, ifstream &infileParkArea){
    infileParkArea.open(IMG_PARK_AREA);
    infilePark.open(IMG_PARK);
    readHeader(infileParkArea);
    readHeader(infilePark);
    //it will only store the interior area of ​​the park, disregarding the limit, so pedestrians will only be positioned there
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            int r, g, b;
            infileParkArea >> r >> g >> b;
            if((r==0 && g==0 && b==0)){
                infilePark >> r >> g >> b;
                if(r!=0 && g!=0 && b!=0){
                    parkArea[i][j] = true;
                }
            }
            else infilePark >> r >> g >> b;
        }
    }
    infileParkArea.close();
    infilePark.close();
}

//positions pedestrians randomly on the floor according to the occupiable positions and the delimited area of ​​the park
void placePedestrians(vector<vd>&floor, vector<vb>&currentMatrix, vector<vb>&parkArea, vector<vi>&heatmap, vector<vi>&reliefProb){
    for(int i=0; i<NUM_PEDESTRIANS; i++){
        int limitX = DIM/2, limitY = DIM/2; 
        while(1){
            //determine which area of ​​the map they will be positioned
            int x = (rand()%limitX)+1, y = (rand()%limitY)+1; //northwest
            //int x = (rand()%limitX)+1+limitX, y = (rand()%limitY)+1+limitY; //southeast
            //int x = (rand()%limitX)+1+limitX, y = (rand()%limitY)+1; //southwest
            //int x = (rand()%limitX)+1, y = (rand()%limitY)+1+limitY; //northeast
            //int x = (rand()%DIM)+1, y = (rand()%DIM)+1;

            if(floor[x][y]<999 && currentMatrix[x][y]==false && parkArea[x][y]==true){
                currentMatrix[x][y] = true;
                heatmap[x][y]++; //simulations considering the highway
                /*if(floor[x][y] != 1){ //simulations don't considering the highway
                    heatmap[x][y]++;
                }*/
                break;
            }
        }
    }
}

void updatePreviousPedestrianMatrix(vector<vb>&currentMatrix, vector<vb>&previousMatrix){
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            previousMatrix[i][j] = currentMatrix[i][j];
        }
    }
}

void checkConflicts(vector<vb>&previousMatrix, vector<vb>&currentMatrix, vector<vd>&floor, vector<vd>&highwayFloor, vector<vi>&reliefProb, vector<vd>&vegProb, vector<vi>&posCount, vector<vi>&fireBlock, int &numTrapped){
    for(int x=1; x<=DIM; x++){
        for(int y=1; y<=DIM; y++){
            //if it is occupied, add +1 to the conflict cell in which you intend to make the move
            if(previousMatrix[x][y]){
                if(posCount[x][y] >= 1 && !previousMatrix[posMov[x][y].first][posMov[x][y].second]){
                    conflictMatrix[posMov[x][y].first][posMov[x][y].second]++;
                    rowsMatrix[conflictMatrix[posMov[x][y].first][posMov[x][y].second]][posMov[x][y].first][posMov[x][y].second] = x;
                    collumnsMatrix[conflictMatrix[posMov[x][y].first][posMov[x][y].second]][posMov[x][y].first][posMov[x][y].second] = y;
                    posCount[x][y] = 0;
                    continue;
                }

                double lowest = __DBL_MAX__;
                int posx=x, posy=y;

                //if it is inside the highway, we will analyze the highway floor, if not, the general floor
                if(floor[x][y] == 1.0){
                    for(int i=0; i<8; i++){
                        if((dx[i] + x) <= 0 || (dx[i] + x) > DIM || (dy[i] + y) <= 0 || (dy[i] + y) > DIM) continue;
                        if(highwayFloor[dx[i]+x][dy[i]+y] > highwayFloor[x][y]) continue; //o pedestre não vai para um floor de valor maior do que aquele em que está
                        //define the lowest floor value
                        if(highwayFloor[dx[i]+x][dy[i]+y] < lowest && !previousMatrix[dx[i]+x][dy[i]+y] && fireBlock[dx[i]+x][dy[i]+y]==0){
                            lowest = highwayFloor[dx[i]+x][dy[i]+y];
                            posx = dx[i]+x;
                            posy = dy[i]+y;
                        }
                    }
                } 
                //if the pedestrian is in a fire alert area, we will first leave it
                else if(fireBlock[x][y] != 0){
                    for(int i=0; i<8; i++){
                        if((dx[i] + x) <= 0 || (dx[i] + x) > DIM || (dy[i] + y) <= 0 || (dy[i] + y) > DIM) continue;
                        //define the lowest floor value
                        if(fireBlock[dx[i]+x][dy[i]+y] < lowest && !previousMatrix[dx[i]+x][dy[i]+y]){
                            lowest = fireBlock[dx[i]+x][dy[i]+y];
                            posx = dx[i]+x;
                            posy = dy[i]+y;
                        }
                    }
                }
                else{
                    for(int i=0; i<8; i++){
                        if((dx[i] + x) <= 0 || (dx[i] + x) > DIM || (dy[i] + y) <= 0 || (dy[i] + y) > DIM) continue;
                        //the pedestrian will not go to a floor of higher value than the one he is on, unless he is on a high relief
                        if(floor[dx[i]+x][dy[i]+y] > floor[x][y] && reliefProb[x][y] <= reliefProb[dx[i]+x][dy[i]+y]) continue;

                        if(reliefProb[dx[i]+x][dy[i]+y] < reliefProb[x][y]){
                            int aleatorio = (rand() % 100) + 1;
                            if(aleatorio > reliefProb[dx[i]+x][dy[i]+y]) continue; //to consider the probability of relief in the movement
                        }

                        //define the lowest floor value
                        if(floor[dx[i]+x][dy[i]+y] < lowest && !previousMatrix[dx[i]+x][dy[i]+y]){
                            lowest = floor[dx[i]+x][dy[i]+y];
                            posx = dx[i]+x;
                            posy = dy[i]+y;
                        }
                    }
                    if(lowest >= 1000){
                        numTrapped++;
                        previousMatrix[x][y] = currentMatrix[x][y] = false;
                        continue;
                    }
                }
                //Acrescentar dificuldade em florestas densas/terrenos acidentados
                //se o pedestre estiver subindo (se movendo de um relevo baixo para um mais alto) terá dificuldade na movimentação
                if((reliefProb[posx][posy] > reliefProb[x][y]) || (vegProb[x][y] >= 0.5)){
                    posCount[x][y]++;
                    if(posCount[x][y] <= 1) {
                        posMov[x][y].first = posx, posMov[x][y].second = posy;
                        continue;
                    }
                    else posCount[x][y] = 0;
                }
                
                conflictMatrix[posx][posy]++;
                //para armazenar a linha e coluna dos pedestres que querem ir para determinada célula do floor
                rowsMatrix[conflictMatrix[posx][posy]][posx][posy] = x;
                collumnsMatrix[conflictMatrix[posx][posy]][posx][posy] = y;
            }
        }
    }
}

void makeMovement(vector<vb>&currentMatrix, vector<vi>&heatmap, vector<vd>&floor){
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            if(conflictMatrix[i][j]>0){
                //will randomly select a pedestrian from the number of pedestrians intending to move to that cell
                int pedestre = (rand()%conflictMatrix[i][j])+1;
                //moves the chosen pedestrian to that cell
                currentMatrix[rowsMatrix[pedestre][i][j]][collumnsMatrix[pedestre][i][j]] = false;
                currentMatrix[i][j] = true;
                heatmap[i][j]++; //simulations considering the highway
                /*if(floor[i][j] != 1){ //simulations don't considering the highway
                    heatmap[i][j]++;
                }*/
            }
        }
    }
}

void checkExit(vector<vb>&currentMatrix, vector<vd>&highwayFloor, int &qtdFugaPedestres, int k){
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            if(highwayFloor[i][j]==1 && currentMatrix[i][j]){
                currentMatrix[i][j] = false;
                qtdFugaPedestres++;
            }
            
        }
    }
}

void move(vector<vb>&currentMatrix, vector<vb>&previousMatrix, vector<vd>&floor, vector<vd>&highwayFloor, vector<vi>&heatmap, vector<vi>&reliefProb, vector<vd>&vegProb, vector<vi>&posCount, vector<vi>&fireBlock, int &numTrapped){
    initializeConflicts();
    updatePreviousPedestrianMatrix(currentMatrix, previousMatrix);
    checkConflicts(previousMatrix, currentMatrix, floor, highwayFloor, reliefProb, vegProb, posCount, fireBlock, numTrapped);
    makeMovement(currentMatrix, heatmap, floor);
}