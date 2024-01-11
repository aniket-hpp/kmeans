/*
    Author: Aniket Biswas
    Setsup the matrix
    Github: https://github.com/aniket-hpp
*/


#ifndef SETUP_MATRIX_H
#define SETUP_MATRIX_H

#include <stdio.h>
#include <ctype.h>
#include "../shared/shared.h"
#include "./logerr.h"

// Counts the rows and columns by counting spaces and next-line 
void count_rows_cols(){
    logerr(NULL, "LOG: started counting rows and columns for data-points in file");
    fseek(fp, 0L, SEEK_SET);
    char ch;

    while((ch = fgetc(fp)) != EOF){
        if(ch == ' ') cols++;
        if(ch == '\n') rows++;
    }

    if(rows < 2) crash(NULL, "err: clustering requires atleast three datapoint");

    rows++;
    cols = cols/rows + 1;

    logerr(NULL, "LOG: completed counting rows and columns for data-points in file");
    fseek(fp, 0L, SEEK_SET);
}

// Copies the data from file to heap memory
void setup_matrix(){
    crash(matrix, "err: recieved null pointer in 'setup_matrix' function");
    logerr(NULL, "LOG: started setting up data-points from file to memory");
    int row_index = 0, col_index = 0; 
    int muliplier = 10, buffer = 0;
    char sign = 1;

    char ch;
    while(1){
        ch =  fgetc(fp);
        switch(ch){
            case EOF: {
                matrix[row_index].arr[col_index] = sign * buffer;
                fclose(fp);
                logerr(NULL, "LOG: completed setting up data-points from file to memory");
                return;
            }

            case '-': {
                if(buffer != 0) crash(NULL, "err: misplaced negative sign '-'");
                sign = -1;
                break;
            }

            case ' ': {
                matrix[row_index].arr[col_index++] = sign * buffer;
                buffer = 0;
                if(col_index >= cols) crash(NULL, "err: no of columns exceeded than initial columns");
                sign = 1;
                muliplier = 10;
                break;
            }

            case '\n': {
                matrix[row_index++].arr[col_index] = sign * buffer; 
                buffer = 0;
                if(row_index >= rows) crash(NULL, "err: no of rows exceeded than initial rows");
                col_index = 0;
                sign = 1;
                muliplier = 10;
                break;
            }

            default:
                if(!isdigit(ch)) crash(NULL, "err: unknown token rather than digit");
                buffer = (buffer * muliplier) + (ch - 48);
       } 
    }
}

#endif