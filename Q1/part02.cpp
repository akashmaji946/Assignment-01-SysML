#include<iostream>
#include<bits/stdc++.h>
using namespace std;


/* Parameters given in the question */
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
*/
#define Ux 1
#define Uy 1
#define E 28
#define F 28

double OUTPUT[N][M][F][E];
double INPUT[N][C][H][W];
double FILTER[M][C][R][S];

double BIAS[M];

double OUTPUT_FLAT[N][M][E * F];
double INPUTS_FLAT[N][C * R * S][E * F];
double FILTERS_FLAT[M][C * R * S];

void toeplitz_multiply() {
    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            for (int e = 0; e < E * F; ++e) {
                OUTPUT_FLAT[n][m][e] = BIAS[m];
                for (int crs = 0; crs < C * R * S; ++crs) {
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

void read_biases(){
    FILE* file = fopen("BIAS.txt", "r");
    assert(file != 0);
    for(int m = 0; m < M; m++){
        fscanf(file, "%lf", &BIAS[m]);
    }
    fclose(file);
}

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

    // init_INPUT();
    // print_INPUTS();
    // flatten_inputs();
    // print_INPUTS_FLAT();

    read_inputs();
    read_filters();
    read_biases();

    flatten_inputs();
    flatten_filters();

    toeplitz_multiply();
    save_outputs();





    return 0;
}