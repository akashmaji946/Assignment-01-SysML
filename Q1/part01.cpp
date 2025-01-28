/*
* Author: Akash Maji
* Email: akashmaji@iisc.ac.in
*/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

/* Parameters with usual meaning given in the question */
/*
N: Number of input feature maps (Batch size)
C: Number of input channels
H: Height of the input feature map
W: Width of the input feature map
R: Height of the filter/kernel
S: Width of the filter/kernel
M: Number of output channels (number of filters)
E: Height of the output feature map after convolution
F: Width of the output feature map after convolution
Ux: stride along x
Uy: stride along y
*/
#define N 8
#define M 32
#define H 32
#define W 32
#define R 5
#define S 5
#define C 4

/* Let us compute the size of OUTPUT map */
/*
Since, INPUT is 32*32 and FILTER is 5*5
So, OUTPUT will be 28*28 assuming stride=1

Formula: E * F = (H-R+1)*(W-S+1) for stride=1

*/
#define Ux 1
#define Uy 1
#define E 28
#define F 28


double OUTPUT[N][M][F][E];
double INPUT[N][C][H][W];
double FILTER[M][C][R][S];

double BIAS[M];

/*Create a random device and a generator */ 
std::random_device rd;  
std::mt19937 gen(rd());   
// Define the range as in question
std::uniform_real_distribution<> dis(-1.0, 1.0);   
double randomFloat;

double get_random_value(){
    return dis(gen);
}

/* initialize OUTPUT, INPUT, FILTER, BIAS maps */
void initialize_structures(){

    memset(OUTPUT, 0, N*M*F*E*sizeof(double));
    memset(INPUT, 0, N*C*H*W*sizeof(double));
    memset(FILTER, 0, M*C*R*S*sizeof(double));
    memset(BIAS, 0, M*sizeof(double));

    for(int n = 0; n < N; n++){
        for(int c = 0; c < C; c++){
            for(int h = 0; h < H; h++){
                for(int w = 0; w < W; w++ ){
                    INPUT[n][c][h][w] = get_random_value();
                }
            }
        }
    }
    for(int m = 0; m < M; m++){
        for(int c = 0; c < C; c++){
            for(int r = 0; r < R; r++){
                for(int s = 0; s < S; s++ ){
                    FILTER[m][c][r][s] = get_random_value();
                }
            }
        }
    }
    for(int m = 0; m < M; m++){
        BIAS[m] = get_random_value();
    }
}

/* save the values into respective files */
void save_to_files(){
    FILE* file;

    file = fopen("INPUT.txt", "w");
    assert(file != 0);
    for(int n = 0; n < N; n++){
        for(int c = 0; c < C; c++){
            for(int h = 0; h < H; h++){
                for(int w = 0; w < W; w++ ){
                    fprintf(file, "%lf ", INPUT[n][c][h][w]);
                }
            }
        }
    }
    fclose(file);


    file = fopen("FILTER.txt", "w");
    assert(file != 0);
    for(int m = 0; m < M; m++){
        for(int c = 0; c < C; c++){
            for(int r = 0; r < R; r++){
                for(int s = 0; s < S; s++ ){
                    fprintf(file, "%lf ", FILTER[m][c][r][s]);
                }
            }
        }
    }
    fclose(file);

    file = fopen("BIAS.txt", "w");
    assert(file != 0);
    for(int m = 0; m < M; m++){
        fprintf(file, "%lf ", BIAS[m]);
    }
    fclose(file);

}

void save_output(){
    FILE* file;
    file = fopen("OUTPUT1.txt", "w");
    assert(file != 0);
    for(int n = 0; n < N; n++){
        for(int m = 0; m < M; m++){
            for(int f = 0; f < F; f++){
                for(int e = 0; e < E; e++ ){
                    fprintf(file, "%lf\n", OUTPUT[n][m][f][e]);
                }
            }
        }
    }
    fclose(file);
}

/* implemenatation idea taken from course slides */
void naive_convolution(){
     // Naive 7-layer loop implementation
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            for (int x = 0; x < F; x++) {
                for (int y = 0; y < E; y++) {
                    // Initialize the output value with bias
                    OUTPUT[n][m][x][y] = BIAS[m];
                    for (int i = 0; i < R; i++) {
                        for (int j = 0; j < S; j++) {
                            for (int k = 0; k < C; k++) {
                                OUTPUT[n][m][x][y] += INPUT[n][k][Ux * x + i][Uy * y + j] * FILTER[m][k][i][j];
                            }
                        }
                    }
                }
            }
        }
    }
}



int main(){
    // initialize with random values
    initialize_structures();
    // save the files so that toeplitz convolution can use
    // them for performance comparison, and same inputs, filters, bias.
    save_to_files();
    // do naive convolution using 7-layer loop
    naive_convolution();
    // save the output into OUTPUT1.txt
    save_output();

    return 0;
}
