//included libraries
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <time.h>
#include <cstring>
#include <iomanip>
#include <limits.h>
using namespace std;

//abbreviations
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef vector<pair<int, int>> vpi;

#define DIM 200 //matrix dimensions
#define NUM_ITERATIONS 300 //number of iterations
#define NUM_PEDESTRIANS 100//number of pedestrians

#define IMG_PARK "images/area/park.ppm" //defines the ppm image of the park with vegetation
#define IMG_PARK_AREA "images/area/park_area.ppm" //defines the ppm image of the park area with boundaries
#define IMG_RELIEF "images/area/relief.ppm"
#define IMG_INTERVAL_0 "images/iterations/image0.ppm"
#define IMG_INTERVAL_1 "images/iterations/image1.ppm"
#define IMG_INTERVAL_2 "images/iterations/image2.ppm"
#define IMG_INTERVAL_3 "images/iterations/image3.ppm"
#define IMG_INTERVAL_4 "images/iterations/image4.ppm"
#define IMG_INTERVAL_5 "images/iterations/image5.ppm"
#define SIMUL_FILE "result_files/simulation_result.txt"
#define HEATMAP_FILE "result_files/heatmap.txt"

//to be able to visit neighboring cells
const int dx[] = {1, 0, -1, 0, 1, -1, 1, -1};
const int dy[] = {0, 1, 0, -1, 1, -1, -1, 1};

//floor field
void initializeFloor(vector<vd>&floor, ifstream &infile, vector<vd>&vegProb);
void printFloor(vector<vd>&floor, ofstream &outfile);
void calculateFloorValue(vector<vd>&floor, vector<vd>&vegProb);
void initializeHighwayFloor(vector<vd>&highwayFloor, ifstream &infile);
void calculateHighwayFloorValue(vector<vd>&highwayFloor);

//pedestrian movement
void placePedestrians(vector<vd>&floor, vector<vb>&currentMatrix, vector<vb>&parkArea, vector<vi>&heatmap, vector<vi>&reliefProb);
void move(vector<vb>&currentMatrix, vector<vb>&previousMatrix, vector<vd>&floor, vector<vd>&highwayFloor, vector<vi>&heatmap, vector<vi>&reliefProb, vector<vd>&vegProb, vector<vi>&posCount, vector<vi>&fireBlock, int &numTrapped);
void checkExit(vector<vb>&currentMatrix, vector<vd>&highwayFloor, int &numEscapedPedestrians, int k);
void defineParkArea(vector<vb>&parkArea, ifstream &parkInfile, ifstream &parkAreaInfile);

//auxiliary functions
void printHeader(ofstream &outfile);
void printMatrix(vector<vb>&currentPedestrianMatrix, vector<vd>&floor, ifstream &infile, ofstream &outfile, int k, vector<vi>&fireBlock, vector<vi>&fireState);
void readHeader(ifstream &infile);
void printHeatmap(vector<vi>&heatmap, ofstream &heatmapFile);
void resetMatrices(vector<vb>&currentPedestrianMatrix, vector<vb>&previousPedestrianMatrix, vector<vi>&currentFireMatrix, vector<vi>&previousFireMatrix, vector<vi>&fireBlock);
void occupancyPercentage(ifstream &infile);

//probabilities
void calculateVegetationProbability(vector<vd>&vegProb, ifstream &infile);
void calculateReliefProbability(vector<vi>&reliefProb, ifstream &infile);

//fire propagation
void updatefireBlock(vector<vi>&fireState, vector<vi>&fireBlock, vector<vd>&floor);
void changeCellState(vector<vi>&currentFireState, vector<vi>&previousFireState, vector<vd>&vegProb, vector<vd>&floor);
void initializeFireMatrix(vector<vi>&currentFireState, vector<vd>&floor, vector<vb>&parkArea);
void updatePreviousFireState(vector<vi>&currentFireState, vector<vi>&previousFireState);
void updateFloorWithFire(vector<vi>&fireBlock, vector<vd>&floor);
void calculateBurnPercentage(vector<vi>&currentFireState, int k);