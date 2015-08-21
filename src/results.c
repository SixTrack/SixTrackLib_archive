#include <stdio.h>
#include <math.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

FLOAT printPartf[14]={0};

void print_var(INT elemi[], FLOAT elemf[], INT parti[], FLOAT partf[], INT elem_type){
    INT i;
    for(i=0;i<14;i++){
        printPartf[i]=partf[i];
    }
}

void print_comp(FLOAT partf[]){

    INT i;
    FLOAT err[13]={0};

    for(i=0;i<14;i++){
        err[i] = sqrt(pow((partf[i]-printPartf[i]),2));
    }

    printf("%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n\n",
        "s",err[12],partf[12],printPartf[12],"x",err[5],partf[5],printPartf[5],
        "px",err[6],partf[6],printPartf[6],"y",err[7],partf[7],printPartf[7],
        "py",err[8],partf[8],printPartf[8],"tau",err[9],partf[9],printPartf[9],
        "delta",err[11],partf[11],printPartf[11],"pt", err[10],partf[10],printPartf[10]);
}