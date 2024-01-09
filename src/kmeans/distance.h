/*
    Author: Aniket Biswas
    Computes the distance
    Github: https://github.com/aniket-hpp
*/

#ifndef DISTANCE_H
#define DISTANCE_H

#include "../shared/shared.h"
#include <math.h>

// computes the euclidean-distance between two given points
float distance(int *x, int *y){
    crash((!x || !y)?NULL:x, "err: recieved null pointer in 'distance' function");
    logerr(NULL, "LOG: calcualting distance between data-points");

    float sum = 0.0f;

    for(int i = 0; i < cols; i++){
        sum += pow(x[i] - y[i], 2); 
    }

    return sqrt(sum);
}

#endif