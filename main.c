/*
    Author: Aniket Biswas
    Reads data-points from a file, generates clusters using kmeans algortihm and stores them in output.txt 
    Github: https://github.com/aniket-hpp

    kmeans <no-of-clusters> <file>

    FORMAT FOR INPUT DATAPOINTS:
    ROWS COLS->
    .    a b c
    .    d e f
    .    g h i
    .    j k l

    1. Columns should be separted using with one space ' '
    2. Rows should be sepated using one next-line '\n'

    Use random.c to generate random data-points.
*/

#include <stdio.h>

#include "./src/include/logerr.h"
#include "./src/include/setup_matrix.h"
#include "./src/shared/shared.h"
#include "./src/kmeans/kmeans.h"
#include "./src/kmeans/print_cluster.h"
#include "./src/include/data_point.h"


int main(int argc, char *argv[]){
    if(argc < 3){
        printf("kmeans: usage:\nkmeans <number-of-clusters> <file>\n");
        exit(0);
    }
    
    // sets number of clusters
    K = atoi(argv[1]);
    // opens the file
    fp = fopen(argv[2], "r");
    crash(fp, "err: failed to open file");    
    
    // counts row & cols
    count_rows_cols();

    // clusters to be made can not be less than the rows
    if(K > rows){
        crash(NULL, "err: number of clusters to be made is greater than data-points");
    }

    // allocating memory for the matrix
    matrix = make_matrix(rows, cols);
    // setting up the matrix with data
    setup_matrix();

    //starts clustering
    start_kmeans_clustering();
    // cleanup
    delete_matrix(matrix, rows);
}