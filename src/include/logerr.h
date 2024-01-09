/*
    Author: Aniket Biswas
    Error Handler
    Github: https://github.com/aniket-hpp
*/

#ifndef LOGERR_H
#define LOGERR_H

#include <stdio.h>
#include <stdlib.h>

// logs an error or msg
void logerr(void *ptr, const char *err){
    if(ptr == NULL){
        fprintf(stderr, "%s\n", err);                
    }
}

// logs the error and quits the executio
void crash(void *ptr, const char *err){
    if(ptr == NULL){
        logerr(NULL, err);
        exit(1);
    }
}

#endif