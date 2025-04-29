#include "utils.h"

int main(){
    //system matrices
    vector <vd> floor(DIM+1, vd(DIM+1, 0));
    vector <vd> highwayFloor(DIM+1, vd(DIM+1, 0));
    vector <vb> parkArea(DIM+1, vb(DIM+1, 0));
    vector <vd> vegProb(DIM+1, vd(DIM+1, 0));
    vector <vi> reliefProb(DIM+1, vi(DIM+1, 0));
    vector <vb> currentPedestriansMatrix(DIM+1, vb(DIM+1, false));
    vector <vb> previousPedestriansMatrix(DIM+1, vb(DIM+1, false));
    vector <vi> heatmap(DIM+1, vi(DIM+1, 0));
    vector <vi> posCount(DIM+1, vi(DIM+1, 0));
    vector <vi> currentFireState(DIM+1, vi(DIM+1, 0));
    vector <vi> previousFireState(DIM+1, vi(DIM+1, 0));
    vector <vi> fireBlock(DIM+1, vi(DIM+1, 0));

    ifstream infilePark, infileparkArea;
    ofstream probOutFile(SIMUL_FILE);
    ofstream heatmapFile;
    defineParkArea(parkArea, infilePark, infileparkArea);
    calculateReliefProbability(reliefProb, infilePark);
    calculateVegetationProbability(vegProb, infilePark);
    initializeFloor(floor, infilePark, vegProb);
    initializeHighwayFloor(highwayFloor, infilePark);
    
    for(int i=1; i<=100; i++){
        srand(i);
        int numEscapedPedestrians = 0;
        int numTrapped = 0;
        int finalIt = 0;

        initializeFireMatrix(currentFireState, floor, parkArea);
        placePedestrians(floor, currentPedestriansMatrix, parkArea, heatmap, reliefProb);

        for(int k=1; k<=NUM_ITERATIONS; k++){
            updatefireBlock(currentFireState, fireBlock, floor);
            updateFloorWithFire(fireBlock, floor);
            move(currentPedestriansMatrix, previousPedestriansMatrix, floor, highwayFloor, heatmap, reliefProb, vegProb, posCount, fireBlock, numTrapped);
            checkExit(currentPedestriansMatrix, highwayFloor, numEscapedPedestrians, k);

            if(numEscapedPedestrians==NUM_PEDESTRIANS && finalIt==0){
                finalIt = k;
            }

            if(k%50==0){
                probOutFile << numEscapedPedestrians << "\t";
            }
            
            //the fire state only updates every 10 iterations
            if(k%10 == 0){
                updatePreviousFireState(currentFireState, previousFireState);
                changeCellState(currentFireState, previousFireState, vegProb, floor);
            }
        }
        probOutFile << numEscapedPedestrians << "\t" << numTrapped << "\t" << i << "\n";
        resetMatrices(currentPedestriansMatrix, previousPedestriansMatrix, currentFireState, previousFireState, fireBlock);
        initializeFloor(floor, infilePark, vegProb);
    }
    
    probOutFile.close();
    printHeatmap(heatmap, heatmapFile);

    return 0;
}