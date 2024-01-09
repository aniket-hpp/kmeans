/*
    Author: Aniket Biswas
    Different Printing Functions
    Github: https://github.com/aniket-hpp
*/

#ifndef PRINT_CLUSTER_H
#define PRINT_CLUSTER_H

#include <stdio.h>
#include "../shared/shared.h"
#include "../include/data_point.h"

void print_cluster(FILE *stream, DataPoints *cluster, int rows, int cols, int cluster_no){
    crash((!stream || !cluster)?NULL:stream, "err: recieved null pointer in 'print_cluster' function");
    putc('[', stream);

    for(int i = 0; i < rows; i++){
        if(cluster[i].cluster != cluster_no) continue;

        putc('{', stream);

        for(int j = 0; j < cols; j++){
            printf("%d%s", cluster[i].arr[j], (j < cols-1)?", ":"");
        }

        putc('}', stream);
        fputs((i < rows - 1)?", ":"", stream);
    }

    fputs("]\n", stream);
}

void print_final_cluster(){
    for(int i = 0; i < K; i++){
        printf("CLUSTER %d:\n", i);
        print_cluster(stdout, matrix, rows, cols, i);
    }
}

void print_centers(int **k_centers){
    crash(k_centers, "err: recieved null pointer in 'print_centers' function");
    logerr(NULL, "CLUSTER CENTERS: ");

    for(int i = 0; i < K; i++){
        printf("V%d: ", i);
        for(int j = 0; j < cols; j++){
            printf("%d ", k_centers[i][j]);
        }
        printf("\n");
    }
}

#endif