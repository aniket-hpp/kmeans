/*
    Author: Aniket Biswas
    Clusters Data Points
    Github: https://github.com/aniket-hpp
*/

#ifndef KMEANS_H
#define KMEANS_H

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../include/data_point.h"
#include "../shared/shared.h"
#include "./distance.h"
#include "./random.h"
#include "./print_cluster.h"
#include "../include/logerr.h"

// copies current cluster information of the data-points to the given array
void copy_cluster_id(int *cluster_id){
    crash(cluster_id, "err: recieved null-pointer in 'copy_cluster_id' function");
    logerr(NULL, "LOG: copying clusters ids");
    for(int i = 0; i < rows; i++){
        cluster_id[i] = matrix[i].cluster;
    }
}

// checks if the datapoints have changed clusters or not after clustering
int is_cluster_id_same(int *cluster_id){
    crash(cluster_id, "err: recieved null-pointer in 'copy_cluster_id' function");
    logerr(NULL, "LOG: comparing cluster ids"); 

    for(int i = 0; i < rows; i++)
        if(cluster_id[i] != matrix[i].cluster){
           return 0;
        } 

    return 1;
}

// finds & returns the index of the minimum distance [Cluster]
int minimum_distance(float *dist){
    crash(dist, "err: recieved null-pointer in 'minimum_distance' function");
    logerr(NULL, "LOG: calculating minimum distance ");

    int k = 0;

    for(int i = 1; i < K; i++)
        if(dist[i] < dist[k]) k = i;

    return k;
}

// makes new data-points from the newly formed clusters by taking averages
void make_avg_k_centers(int **k_centers){
    crash(k_centers, "err: recieved null-pointer in 'make_avg_k_centers' function");
    logerr(NULL, "LOG: calculating new cluster-centers");

    // stores no of data-points in an cluster
    int count[K];
    memset(count, 0, K*sizeof(int));
    
    // stores the sum of each data-points in an cluster
    int **sums = malloc(K * sizeof(int *));
    crash(sums, "err: failed to allocate memory for 'sums' in 'make_avg_k_centers' function");

    // memory-allocation
    for(int r = 0; r < K; r++){
        sums[r] = malloc(cols * sizeof(int));
        crash(sums[r], "err: failed to allocate memory for 'sums[r]' in make_avg_k_centers function");
        memset(sums[r], 0, cols * sizeof(int));
    }

    // counting and summing of data-points
    for(int r = 0; r < rows; r++){
        count[matrix[r].cluster]++;

        for(int c = 0; c < cols; c++)
            sums[matrix[r].cluster][c] += matrix[r].arr[c];
    }

    // computing the average and storing it in the given pointer
    for(int k = 0; k < K; k++){
        for(int c = 0; c < cols; c++){
            sums[k][c] /= count[k];
        }

        k_centers[k] = sums[k];       
    }
}

// deallocates all the allocated data for the cluster centers
void delete_avg_k_centers(int **k_centers){
    crash(k_centers, "err: recieved null-pointer in 'delete_avg_k_centers' function");

    for(int k = 0; k< K; k++){
        free(k_centers[k]);
    }

    logerr(NULL,"LOG: released memory from allocated 'k_centers'");
}

// Clusters data-points based on distance
void __kmeans_clustering(int **k_centers){
    crash(k_centers, "err: recieved null-pointer in '__kmeans_clustering' function");
    logerr(NULL, "LOG: applying k-means clustering");
    
    // stores calculated distance
    float dist[K];

    for(int i = 0; i < rows; i++){
        // finds the distance between two data-points
        for(int j = 0; j < K; j++)
            dist[j] = distance(matrix[i].arr, k_centers[j]);

        // assigns the cluster_id that have minimum distance from the centers
        matrix[i].cluster = minimum_distance(dist);
    }
}

// writes the data to the output.txt while formating it
void write_data(){
    fp = fopen("output.txt", "w");
    crash(fp, "err: failed to write results in 'output.txt'");
    logerr(NULL, "LOG: writing data to 'output.txt' file");

    for(int k = 0; k < K; k++){
        fprintf(fp, "CLUSTER=%d\n", k);

        for(int r = 0; r < rows; r++){
            if(matrix[r].cluster == k){
                for(int c = 0; c < cols; c++){
                    fprintf(fp, "%d%s", matrix[r].arr[c], (c < cols-1)?" ":"\n");
                }
            }
        }
    }

    fclose(fp);
}

// starts clustering by setting up required datas
void start_kmeans_clustering(){
    logerr(NULL, "LOG: starting k-means clustering");
    
    // stores the random generated indexes 
    // and points to the rows of data-points
    int k_indexs[K];
    int *k_centers[K];

    // sets everythin to 0 or null
    memset(k_indexs, 0, K * sizeof(int));
    memset(k_centers, 0, K * sizeof(int *));

    // stores a copy of cluster id aka which data-points belongs to which cluster
    int cluster_id[rows];
    copy_cluster_id(cluster_id);

    // initialises the random generator
    srand(time(0));
    generate_random_k_indexes(k_indexs);

    // points to the random rows
    for(int i = 0; i < K; i++)
        k_centers[i] = matrix[k_indexs[i]].arr;
    
    // performs clustering
    __kmeans_clustering(k_centers);

    // loops until the cluster stabilized
    while(!is_cluster_id_same(cluster_id)){
        copy_cluster_id(cluster_id); 
        make_avg_k_centers(k_centers);
        __kmeans_clustering(k_centers);
        delete_avg_k_centers(k_centers);     
    }

    // writing data to the 'output.txt'
    write_data();
}

#endif