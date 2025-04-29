#include "utils.h"

//function to initialize the fire matrix in the first state
void initializeFireMatrix(vector<vi>&currentFireState, vector<vd>&floor, vector<vb>&parkArea) {
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            currentFireState[i][j] = 0;
        }
    }
    int limitX = DIM/2, limitY = DIM/2; 
    while(1){
        //int x = (rand()%limitX)+1, y = (rand()%limitY)+1+limitY; //northeast
        int x = (rand()%limitX)+1+limitX, y = (rand()%limitY)+1; //southwest
        //int x = (rand()%limitX)+1+limitX, y = (rand()%limitY)+1+limitY; //southeast
        //int x = (rand()%limitX)+1, y = (rand()%limitY)+1; //northwest
        //int x = (rand()%DIM)+1, y = (rand()%DIM)+1;
        if(floor[x][y] > 1 && floor[x][y] < 1000 && parkArea[x][y] == true){
            currentFireState[x][y]++;
            break;
        }
    }
}

void updatePreviousFireState(vector<vi>&currentFireState, vector<vi>&previousFireState) {
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            previousFireState[i][j] = currentFireState[i][j];
        }
    }
}

//for iterating through and changing the states of each cell
void changeCellState(vector<vi>&currentFireState, vector<vi>&previousFireState, vector<vd>&vegProb, vector<vd>&floor){
    for (int x = 1; x <= DIM; x++) {
        for (int y = 1; y <= DIM; y++) {
            if(previousFireState[x][y]>0) {
                if(currentFireState[x][y]<5) currentFireState[x][y]++;
            } 
            else if(floor[x][y] == 1000 || floor[x][y] == 1) 
                continue;
            else {
                for(int i = 0; i < 8; i++) {
                    if((dx[i] + x) <= 0 || (dx[i] + x) > DIM || (dy[i] + y) <= 0 || (dy[i] + y) > DIM) continue;
                    if(previousFireState[x + dx[i]][y + dy[i]] > 0) {
                        int randomNumber = (rand() % 100) + 1;
                        if(vegProb[dx[i] + x][dy[i] + y] == 0.8) {
                            if(randomNumber <= 20) currentFireState[x][y]++;
                            break;
                        }
                        else if(vegProb[dx[i] + x][dy[i] + y] == 0.6) {
                            if(randomNumber <= 40) currentFireState[x][y]++;
                            break;
                        }
                        else if(vegProb[dx[i] + x][dy[i] + y] == 0.5) {
                            if(randomNumber <= 50) currentFireState[x][y]++;
                            break;
                        }
                        else if(vegProb[dx[i] + x][dy[i] + y] == 0.4) {
                            if(randomNumber <= 60) currentFireState[x][y]++;
                            break;
                        }
                        else if(vegProb[dx[i] + x][dy[i] + y] == 0.3) {
                            if(randomNumber <= 70) currentFireState[x][y]++;
                            break;
                        }
                        else if(vegProb[dx[i] + x][dy[i] + y] == 0.2) {
                            if(randomNumber <= 80) currentFireState[x][y]++;
                            break;
                        }
                        else if(vegProb[dx[i] + x][dy[i] + y] == 0.1) {
                            if(randomNumber <= 90) currentFireState[x][y]++;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void updatefireBlock(vector<vi>&fireState, vector<vi>&fireBlock, vector<vd>&floor){
    for(int x=1; x<=DIM; x++){
        for(int y=1; y<=DIM; y++){
            if(fireState[x][y] == 1){
                fireBlock[x][y] = 1000;

                for(int i=0; i<8; i++){
                    for(int k=1; k<=5; k++){
                        if((dx[i]*k + x) <= 0 || (dx[i]*k + x) > DIM || (dy[i]*k + y) <= 0 || (dy[i]*k + y) > DIM) continue;
                        if(fireBlock[dx[i]*k+x][dy[i]*k+y] == 1000) continue;
                        if(floor[dx[i]*k+x][dy[i]*k+y] == 1000 || floor[dx[i]*k+x][dy[i]*k+y] == 1) continue;
                        if(fireBlock[dx[i]*k+x][dy[i]*k+y] < fireBlock[(dx[i]*k+x)-dx[i]][(dy[i]*k+y)-dy[i]] - 1){
                            fireBlock[dx[i]*k+x][dy[i]*k+y] = fireBlock[(dx[i]*k+x)-dx[i]][(dy[i]*k+y)-dy[i]] - 1;
                        }
                    }
                }
            }
        }
    }
}

void updateFloorWithFire(vector<vi>&fireBlock, vector<vd>&floor){
    for(int x=1; x<=DIM; x++){
        for(int y=1; y<=DIM; y++){
            if(fireBlock[x][y] > 0){
                floor[x][y] = 1001;
            }
        }
    }
}

void calculateBurnPercentage(vector<vi>&currentFireState, int k) {
    int burnedCells = 0;
    for(int i=1; i<=DIM; i++) {
        for(int j=1; j<=DIM; j++) {
            if(currentFireState[i][j] > 0) {
                burnedCells++;
            }
        }
    }

    double burnPerc = (double) burnedCells / (DIM * DIM);
    cout << "Iteracao " << k << "\n";
    cout << "Porcentagem de queimada: " << burnPerc * 100 << "%\n\n";   
}