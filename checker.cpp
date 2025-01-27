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

int main(){
    FILE* output1;
    FILE* output2;

    output1 = fopen("OUTPUT.txt", "r");
    output1 = fopen("OUTPUT2.txt", "r");

    assert(output1 != nullptr);
    assert(output2 != nullptr);

    for(int idx = 0; idx < N*M*F*E; idx++){
        double x = 0, y = 0;
        while (fscanf(output1, "%lf", &x) == 1 && fscanf(output2, "%lf", &y) == 1) {
        if (fabs(x - y) > 0.00001) {
            printf("Difference at index %d: %lf vs %lf\n", idx, x, y);
        }
        idx++;
    }
    }
    printf("All MAtched\n");
    return 0;

}