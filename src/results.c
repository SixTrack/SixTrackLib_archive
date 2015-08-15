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

    // FILE *fptr;
    // fptr=fopen("Output.txt","a");
/*
    switch(elem_type){
        case 0: fprintf(fptr,"ROT2D:\n"); break;
        case 1: fprintf(fptr,"KICK2D:\n"); break;
        case 2: fprintf(fptr,"COUNTER:\n"); break;
        case 4: fprintf(fptr,"MONITOR:\n"); break;
        case 5: fprintf(fptr,"DRIFT_EXACT:\n"); break;
        case 6: fprintf(fptr,"RF_CAVITY:\n"); break;
        case 7: fprintf(fptr,"HORIZONtAL_DIPOLE:\n"); break;
        case 8: fprintf(fptr,"VERTICAL_DIPOLE:\n"); break;
        case 9: fprintf(fptr,"FINAL:\n"); break;
    }

    fprintf(fptr,"elemi: {");
    for(i=0;i<47;i++){
        fprintf(fptr,"%d, ",elemi[i]);
    }
    fprintf(fptr,"%d}\n",elemi[i]);

    fprintf(fptr,"elemf: {");
    for(i=0;i<51;i++){
        fprintf(fptr,"%f, ",elemf[i]);
    }
    fprintf(fptr,"%f}\n",elemf[i]);

    fprintf(fptr,"parti: {");
    for(i=0;i<4;i++){
        fprintf(fptr,"%d, ",parti[i]);
    }
    fprintf(fptr,"%d}\n", parti[i]);

    fprintf(fptr,"partf: {");
    for(i=0;i<13;i++){
        fprintf(fptr,"%f, ",partf[i]);
    }
    fprintf(fptr,"%f}\n\n\n",partf[i]);
*/
    for(i=0;i<14;i++){
        printPartf[i]=partf[i];
    }
    // printf("%-6s %23.16e\n%-6s %23.16e\n%-6s %23.16e\n%-6s %23.16e\n%-6s %23.16e\n%-6s %23.16e\n%-6s %23.16e\n%-6s %23.16e\n\n",
    //     "s",partf[12],"x",partf[5],"px",partf[6],"y",partf[7],"py",partf[8],"tau",partf[9],"delta",partf[11],"pt", partf[10]);
    // fclose(fptr);
}

void print_comp(FLOAT partf[]){

    INT i;
    FLOAT err[13]={0};
    // err=sqrt(sum((ss-pp)**2))
    // if abs(ss)>0 and nn!='tau':
    //   #  err/=abs(ss)

    for(i=0;i<14;i++){
        err[i] = sqrt(pow((partf[i]-printPartf[i]),2));
    }

    printf("%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n\n",
        "s",err[12],partf[12],printPartf[12],"x",err[5],partf[5],printPartf[5],
        "px",err[6],partf[6],printPartf[6],"y",err[7],partf[7],printPartf[7],
        "py",err[8],partf[8],printPartf[8],"tau",err[9],partf[9],printPartf[9],
        "delta",err[11],partf[11],printPartf[11],"pt", err[10],partf[10],printPartf[10]);
}