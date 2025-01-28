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

/*
In Toeplitz matrix generation for flattened FILTER, 
we place the M FILTERS in M rows, 
and each row has all C channels placed one after other. 
So the dimension of W’ is M * CRS,
where R*S is the dimension of a FILTER.
Also, for flattened INPUT, we place C channels one after another vertically downwards. 
The dimension of  INPUTS_FLAT is CRS * EF.

*/
double OUTPUT_FLAT[N][M][E * F];
double INPUTS_FLAT[N][C * R * S][E * F];
double FILTERS_FLAT[M][C * R * S];

void toeplitz_multiply() {
    // 4-layer loop implementation
    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            for (int e = 0; e < E * F; ++e) {
                OUTPUT_FLAT[n][m][e] = BIAS[m];
                for (int crs = 0; crs < C * R * S; ++crs) {
                    /* we multiply the flattened FILTER and flattened INPUT */
                    OUTPUT_FLAT[n][m][e] += FILTERS_FLAT[m][crs] * INPUTS_FLAT[n][crs][e];
                }
            }
        }
    }
}

void flatten_filters(){
    for(int m = 0; m < M; m++){
        int crs = 0;
        for(int c = 0; c < C; c++){
            for(int r = 0; r < R; r++){
                for(int s = 0; s < S; s++ ){
                    FILTERS_FLAT[m][crs++] = FILTER[m][c][r][s];
                }
            }
        }
    }
}

void flatten_inputs(){
    for (int n = 0; n < N; ++n) {  
        for (int c = 0; c < C; ++c) {  
            for (int r = 0; r < R; ++r) {  
                for (int s = 0; s < S; ++s) {  
                    for (int x = 0; x < E; ++x) {  
                        for (int y = 0; y < F; ++y) {  
                            int i = c * R * S + r * S + s;  
                            int j = x * F + y;  
                            INPUTS_FLAT[n][i][j] = INPUT[n][c][x + r][y + s];  
                        }  
                    }  
                }  
            }  
        }  
    } 
}

/* test function for correctness */
void init_INPUT(){
    for (int n = 0; n < N; ++n) {
        for (int c = 0; c < C; ++c) {
            for (int h = 0; h < H; ++h) {
                for (int w = 0; w < W; ++w) {
                    INPUT[n][c][h][w] = n + c + h + w;
                }
            }
        }
    }
}
/* test function for correctness */
void print_INPUTS(){
     for (int n = 0; n < N; ++n) {
        for (int c = 0; c < C; ++c) {
            for (int h = 0; h < H; ++h) {
                for (int w = 0; w < W; ++w) {
                     cout << INPUT[n][c][h][w] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
    }

}
/* test function for correctness */
void print_INPUTS_FLAT() {
    for (int n = 0; n < N; ++n) {
        for (int i = 0; i < C * R * S; ++i) {
            for (int j = 0; j < E * F; ++j) {
                cout << INPUTS_FLAT[n][i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

/* reads in same input used by naive convolution, 
and then it is used for flattening */
void read_inputs(){
    FILE* file = fopen("INPUT.txt", "r");
    assert(file != 0);
    for(int n = 0; n < N; n++){
        for(int c = 0; c < C; c++){
            for(int h = 0; h < H; h++){
                for(int w = 0; w < W; w++ ){
                    fscanf(file, "%lf", &INPUT[n][c][h][w]);
                }
            }
        }
    }
    fclose(file);

}
/* reads in same filter used by naive convolution, 
and then it is used for flattening */
void read_filters(){
    FILE* file = fopen("FILTER.txt", "r");
    assert(file != 0);
    for(int m = 0; m < M; m++){
        for(int c = 0; c < C; c++){
            for(int r = 0; r < R; r++){
                for(int s = 0; s < S; s++ ){
                    fscanf(file, "%lf", &FILTER[m][c][r][s]);
                }
            }
        }
    }
    fclose(file);

}
/* reads in same bias used by naive convolution */
void read_biases(){
    FILE* file = fopen("BIAS.txt", "r");
    assert(file != 0);
    for(int m = 0; m < M; m++){
        fscanf(file, "%lf", &BIAS[m]);
    }
    fclose(file);
}
/* save data into file for comparision */
void save_outputs(){
    FILE* file = fopen("OUTPUT2.txt", "w");
    assert(file != 0);
    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            for (int e = 0; e < E * F; ++e) {
                fprintf(file, "%lf\n", OUTPUT_FLAT[n][m][e]);
            }
        }
    }
    fclose(file);

}

int main(){

    // read same data as used by naive implementation
    read_inputs();
    read_filters();
    read_biases();
    // flatten the maps(toeplitz conversion)
    flatten_inputs();
    flatten_filters();
    // do convolution on same data for output similarity
    toeplitz_multiply();
    // save the output into OUTPUT2.txt
    save_outputs();

    return 0;
}