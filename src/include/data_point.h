/*
    Author: Aniket Biswas
    DataPoints [Rows] DataPoints.arr [Columns]
    Github: https://github.com/aniket-hpp
*/

#ifndef DATA_POINTS
#define DATA_POINTS

#include <stdlib.h>

// data-point struct to create the matrix
// which cluster it belong can be achieved by setting th cluster field
typedef struct{
    int *arr;
    int cluster;
}DataPoints;

// Allocates memory for the matrix
DataPoints* make_matrix(int rows, int cols){
    DataPoints* dp = (DataPoints *)malloc(rows * sizeof(DataPoints));
    crash(dp, "err: memory allocation failed in 'make_matrix' function for data-points");
    logerr(NULL, "LOG: allocated memory for data-points");
    
    for(int i = 0; i < rows; i++){
        dp[i].arr = (int *)malloc(cols*sizeof(int));
        crash(dp[i].arr, "err: memory allocation failed in 'make_matrix' function for arrays");
        dp[i].cluster = 0;
    }

    logerr(NULL, "LOG: allocated memories for arrays and set intial cluster to 0");    
    return dp;
}

// Deallocates all the allocated memory from the matrix
void delete_matrix(DataPoints* dp, int rows){
    for(int i = 0; i < rows; i++)
        free(dp[i].arr);

    free(dp);
    logerr(NULL, "LOG: data-points and arrays are removed from memory");
}

#endif