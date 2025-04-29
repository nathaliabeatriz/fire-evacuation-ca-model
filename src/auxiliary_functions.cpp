#include "utils.h"

//this funtion prints the matrix and stores the iterations in an image format (ppm)
void printMatrix(vector<vb>&currentPedestrianMatrix, vector<vd>&floor, ifstream &infile, ofstream &outfile, int k, vector<vi>&fireBlock, vector<vi>&fireState) {
    infile.open(IMG_PARK);
    readHeader(infile);
    int imageInterval = NUM_ITERATIONS/5;
    //to store 5 images during the simulation

    if(k%imageInterval != 0 && k!=1) return;

    if(k==1){
        outfile.open(IMG_INTERVAL_0, ios::out);
        printHeader(outfile);
    }else if(k==imageInterval){
        outfile.open(IMG_INTERVAL_1, ios::out);
        printHeader(outfile);
    } else if(k==imageInterval*2){
        outfile.open(IMG_INTERVAL_2, ios::out);
        printHeader(outfile);
    } else if(k==imageInterval*3){
        outfile.open(IMG_INTERVAL_3, ios::out);
        printHeader(outfile);
    } else if(k==imageInterval*4){
        outfile.open(IMG_INTERVAL_4, ios::out);
        printHeader(outfile);
    }else if(k==imageInterval*5){
        outfile.open(IMG_INTERVAL_5, ios::out);
        printHeader(outfile);
    }

    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            int r, g, b;
            infile >> r >> g >> b;
            if(fireState[i][j] != 0){
                switch (fireState[i][j]){
                    case 1:
                        outfile << "255\n242\n0\n";
                        break;
                    case 2:
                        outfile << "255\n201\n14\n";
                        break;
                    case 3:
                        outfile << "255\n127\n39\n";
                        break;
                    case 4:
                        outfile << "222\n2\n2\n";
                        break;
                    case 5:
                        outfile << "51\n51\n51\n";
                        break;
                }
            }
            else if(fireBlock[i][j] != 0){
                outfile << "219\n219\n219\n";
            } 
            else if(currentPedestrianMatrix[i][j]){ //para representar os pedestres
                outfile << "255\n0\n195\n";
            }
            else if(fireBlock[i][j] != 0) outfile << "219\n219\n219\n"; 
            else{
                outfile << r << "\n" << g << "\n" << b << "\n";
            }
        }
    }
    outfile.close();
    infile.close();
}

void printHeader(ofstream &outfile){
    outfile << "P3\n";
    outfile << DIM << " " << DIM << "\n";
    outfile << "255\n";
}

void readHeader(ifstream &infile){
    for(int i=0; i<3; i++){
        string l;
        getline(infile, l, '\n');
    }
}

void resetMatrices(vector<vb>&currentMatrixPedestres, vector<vb>&previousMatrixPedestres, vector<vi>&currentMatrixFogo, vector<vi>&previousMatrixFogo, vector<vi>&fireBlock){
    for(int i=0; i<=DIM; i++){
        for(int j=0; j<=DIM; j++){
            previousMatrixPedestres[i][j] = false;
            currentMatrixPedestres[i][j] = false;
            currentMatrixFogo[i][j] = 0;
            currentMatrixFogo[i][j] = 0;
            fireBlock[i][j] = 0;
        }
    }
}

void occupancyPercentage(ifstream &infile){
    infile.open(IMG_PARK);
    readHeader(infile);
    double river=0, park=0, limits=0, highway=0;
    for(int i=1; i<=DIM; i++){
        for(int i=1; i<=DIM; i++){
            int r, g, b;
            infile >> r >> g >> b;
            if(r==0 && g==0 && b==0) limits++;
            else if((r==95 && g==96 && b==97) || (r==100 && g==100 && b==100)) highway++;
            else if(r==34 && g==177 && b==76) park++;
            else if(r==66 && g==72 && b==245) river++;
        }
    }
    infile.close();
    cout << "\nPorcentagens de ocupacao:\n";
    cout << "Rio: " << (river/(double)(DIM*DIM))*100 << "%\n";
    cout << "Parque: " << (park/(double)(DIM*DIM))*100 << "%\n";
    cout << "Limite: " << (limits/(double)(DIM*DIM))*100 << "%\n";
    cout << "Rodovia: " << (highway/(double)(DIM*DIM))*100 << "%\n";
}

void printHeatmap(vector<vi>&heatmap, ofstream &heatmapFile){
    heatmapFile.open(HEATMAP_FILE);
    for(int i=1; i<=DIM; i++){
        for(int j=1; j<=DIM; j++){
            heatmapFile << (double)heatmap[i][j]/100.0 << " ";
        }
        heatmapFile << "\n";
    }
    heatmapFile.close();
}
    