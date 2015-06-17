#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

void print_var(INT elemi[], FLOAT elemf[], INT parti[], FLOAT partf[], INT elem_type){
    INT i;

    FILE *fptr;
    fptr=fopen("Output.txt","a");

    switch(elem_type){
        case 0: fprintf(fptr,"ROT2D:\n"); break;
        case 1: fprintf(fptr,"KICK2D:\n"); break;
        case 2: fprintf(fptr,"COUNTER:\n"); break;
        case 4: fprintf(fptr,"FINAL:\n"); break;
    }

    fprintf(fptr,"elemi: {");
    for(i=0;i<27;i++){
        fprintf(fptr,"%d, ",elemi[i]);
    }
    fprintf(fptr,"%d}\n",elemi[i]);

    fprintf(fptr,"elemf: {");
    for(i=0;i<6;i++){
        fprintf(fptr,"%f, ",elemf[i]);
    }
    fprintf(fptr,"%f}\n",elemf[i]);

    fprintf(fptr,"parti: {");
    for(i=0;i<4;i++){
        fprintf(fptr,"%d, ",parti[i]);
    }
    fprintf(fptr,"%d}\n", parti[i]);

    fprintf(fptr,"partf: {");
    for(i=0;i<1;i++){
        fprintf(fptr,"%f, ",partf[i]);
    }
    fprintf(fptr,"%f}\n\n\n",partf[i]);

    fclose(fptr);
}