#include "utils.h"

//initial floor field values, considering the exits
void initializeFloor(vector<vd>&floor, ifstream &infile, vector<vd>&vegProb){
    infile.open(IMG_PARK);
    readHeader(infile);
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            int r, g, b;
            infile >> r >> g >> b;
            //it will be not possible to pass through limit and hidrography cells and the only exit will be through the highway
            if((r==0 && g==0 && b==0) || (r==66 && g==72 && b==245)){
                floor[i][j] = 1000.0;
            } else if((r==95 && g==96 && b==97) || (r==100 && g==100 && b==100)){
                floor[i][j] = 1.0;
            } else {
                floor[i][j] = 999.0;
            }
        }
    }
    infile.close();
    calculateFloorValue(floor, vegProb);
}

void calculateVegetationProbability(vector<vd>&vegProb, ifstream &infile){
    infile.open(IMG_PARK);
    readHeader(infile);
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            int r, g, b;
            infile >> r >> g >> b;
            if(r == 33 && g == 80 && b == 31){ //Gallery Forest
                vegProb[i][j] = 0.8;
            } else if(r == 53 && g == 178 && b == 76){ //Forest Formation
                vegProb[i][j] = 0.6;
            } else if(r == 89 && g == 139 && b == 66){ //Wooded-Stepic Savanna
                vegProb[i][j] = 0.3;
            } else if(r == 200 && g == 186 && b == 51){ //Typical Cerrado
                vegProb[i][j] = 0.4;
            } else if(r == 243 && g == 237 && b == 27){ //Rupestrian Cerrado
                vegProb[i][j] = 0.5;
            } else if(r == 105 && g == 92 && b == 50){ //Shrub-Grass Stepic Savanna
                vegProb[i][j] = 0.2;
            } else if(r == 228 && g == 220 && b == 95){ //Dirty Field
                vegProb[i][j] = 0.1;
            }
        }
    }
    infile.close();
}

void calculateReliefProbability(vector<vi>&reliefProb, ifstream &infile){
    infile.open(IMG_RELIEF);
    readHeader(infile);
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            int r, g, b;
            infile >> r >> g >> b;
            if((r==255 && g==255 && b==255) || (r==95 && g==96 && b==97)){
                reliefProb[i][j] = 100;
            } else if(r==45 && g==0 && b==74){
                reliefProb[i][j] = 50;
            } else if(r==0 && g==25 && b==209){
                reliefProb[i][j] = 40;
            } else if(r==64 && g==195 && b==0){
                reliefProb[i][j] = 30;
            } else if(r==255 && g==255 && b==0){
                reliefProb[i][j] = 20;
            } else if(r==255 && g==17 && b==17){
                reliefProb[i][j] = 10;
            }
        }
    }

    infile.close();
}


void printFloor(vector<vd>&floor, ofstream &outfile){
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            outfile << floor[i][j] << "\t";
        }
        outfile << endl;
    }
    outfile.close();
}

double findLowestFloorValue(double vet[], int x){
    double lowest = vet[0];
    for(int i=0; i<x; i++){
        if(vet[i] < lowest){
            lowest = vet[i];
        }
    }
    return lowest;
}

void calculateFloorValue(vector<vd>&floor, vector<vd>&vegProb) {
    //the loop will traverse the matrix updating the values from bottom to top and vice versa simultaneously
    //this process will happen twice to guarantee that each cell of the floor stays with the lowest value possible
    for(int cont=0; cont<2; cont++){
        for(int l1=1, l2=DIM; l1<=DIM && l2>=1; l1++, l2--){
            for(int c=1; c<=DIM; c++){
                double values[9];
                int neighbooringCount = 1;
                values[0] = floor[l1][c]; 
                if(floor[l1][c] < 1000 && floor[l1][c] > 1){
                    for(int i=0; i<8; i++){
                        if(l1+dx[i]<1 || l1+dx[i]>DIM || c+dy[i]<1 || c+dy[i]>DIM) continue;
                        if(i<4) values[neighbooringCount] = floor[dx[i]+l1][dy[i]+c] + 1 + vegProb[l1][c];
                        else values[neighbooringCount] = floor[dx[i]+l1][dy[i]+c] + 1.5 + vegProb[l1][c]; 
                        neighbooringCount++;
                    }
                    floor[l1][c] = findLowestFloorValue(values, neighbooringCount);
                }
                neighbooringCount = 1;
                values[0] = floor[l2][c];
                if(floor[l2][c] < 1000 && floor[l2][c] > 1){
                    for(int i=0; i<8; i++){
                        if(l2+dx[i]<1 || l2+dx[i]>DIM || c+dy[i]<1 || c+dy[i]>DIM) continue;
                        if(i<4) values[neighbooringCount] = floor[dx[i]+l2][dy[i]+c] + 1 + vegProb[l2][c];
                        else values[neighbooringCount] = floor[dx[i]+l2][dy[i]+c] + 1.5 + vegProb[l2][c];
                        neighbooringCount++;
                    }
                    floor[l2][c] = findLowestFloorValue(values, neighbooringCount);
                }
            }
        }
    }
}

void initializeHighwayFloor(vector<vd>&highwayFloor, ifstream &infile){
    infile.open(IMG_PARK);
    readHeader(infile);
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            int r, g, b;
            infile >> r >> g >> b;
            if(r==95 && g==96 && b==97){
                highwayFloor[i][j] = 999.0;
            } else if(r==100 && g==100 && b==100){ //pixel 100 100 100 represents the exit of the highway floor field
                highwayFloor[i][j] = 1.0;
            } else{
                highwayFloor[i][j] = 1000;
            }
        }
    }
    infile.close();
    calculateHighwayFloorValue(highwayFloor);
}

void calculateHighwayFloorValue(vector<vd>&highwayFloor) {
    //the loop will traverse the matrix updating the values from bottom to top and vice versa simultaneously
    //this process will happen twice to guarantee that each cell of the floor stays with the lowest value possible
    for(int cont=0; cont<2; cont++){
        for(int l1=1, l2=DIM; l1<=DIM && l2>=1; l1++, l2--){
            for(int c=1; c<=DIM; c++){
                double values[9];
                int neighbooringCount = 1;
                values[0] = highwayFloor[l1][c]; 
                if(highwayFloor[l1][c] < 1000 && highwayFloor[l1][c] > 1){
                    for(int i=0; i<8; i++){
                        if(l1+dx[i]<1 || l1+dx[i]>DIM || c+dy[i]<1 || c+dy[i]>DIM) continue;
                        if(i<4) values[neighbooringCount] = highwayFloor[dx[i]+l1][dy[i]+c] + 1;
                        else values[neighbooringCount] = highwayFloor[dx[i]+l1][dy[i]+c] + 1.5; 
                        neighbooringCount++;
                    }
                    highwayFloor[l1][c] = findLowestFloorValue(values, neighbooringCount);
                }
                neighbooringCount = 1;
                values[0] = highwayFloor[l2][c];
                if(highwayFloor[l2][c] < 1000 && highwayFloor[l2][c] > 1){
                    for(int i=0; i<8; i++){
                        if(l2+dx[i]<1 || l2+dx[i]>DIM || c+dy[i]<1 || c+dy[i]>DIM) continue;
                        if(i<4) values[neighbooringCount] = highwayFloor[dx[i]+l2][dy[i]+c] + 1;
                        else values[neighbooringCount] = highwayFloor[dx[i]+l2][dy[i]+c] + 1.5;
                        neighbooringCount++;
                    }
                    highwayFloor[l2][c] = findLowestFloorValue(values, neighbooringCount);
                }
            }
        }
    }
}
