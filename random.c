/*
    Author: Aniket Biswas
    Generates random number based on range and numbers
    Github: https://github.com/aniket-hpp

    random <max-value-of-each-point> <rows> <columns> <files....
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void write_random(FILE *fp, int max, int rows, int cols){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++)
            fprintf(fp, "%d%s", rand()%max, (c<cols-1)?" ":"");
        fprintf(fp, "%s", (r<rows-1)?"\n":"");
    }
}

int main(int argc, char *argv[]){
    FILE *fp = NULL; 
    srand(time(0));

    if(argc <= 4){
        printf("usage: random <max-value> <rows> <cols> <files....\n");
        exit(1);
    }

    int max = atoi(argv[1]);
    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);

    for(int i = 4; i < argc; i++){
        fp = fopen(argv[i], "w");

        if(fp == NULL){
            printf("random: failed to create file '%s'\n", argv[i]);
            exit(1);
        }

        write_random(fp, max, rows, cols);
        fclose(fp);

        printf("random: wrote random value to '%s'\n", argv[i]);
    }

    exit(0);
}