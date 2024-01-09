/*
    Author: Aniket Biswas
    Random Index Generator
    Github: https://github.com/aniket-hpp
*/

#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include "../shared/shared.h"
#include "../include/logerr.h"

// generates random number, max of the rows
int random_k(){
    return rand() % rows;
}

// search for an element in a array upto a certain length
int find_k(int *k_indexs, int k, int upto){
    for(int i = 0; i < upto; i++)
        if(k == k_indexs[i]) return 1;

    return 0;
}

// generates random number and stores them in the given array
void generate_random_k_indexes(int *k_indexs){
    logerr(NULL, "LOG: generating random numbers");
    k_indexs[0] = random_k();
    int k;

    for(int i = 1; i < K; i++){
        k = random_k();    
        while(find_k(k_indexs, k, i)){
            k = random_k();
        }

        k_indexs[i] = k;
    }
}

#endif