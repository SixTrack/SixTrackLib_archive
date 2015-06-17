#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

void print_var(INT [], FLOAT [], INT [], FLOAT [], INT);

inline void kick2d_calc(INT i, INT j, FLOAT k, INT o, FLOAT partf[]){
   partf[j]+=k*pow(partf[i],o);
}

INT kick2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    GETATTRF(kick2d,k);
    GETATTRI(kick2d,i);
    GETATTRI(kick2d,j);
    GETATTRI(kick2d,o);
    INITPARTF;
    for(partid=0;partid<partn;partid++){
      kick2d_calc(i,j,k,o,GETPARTF(partid));
    };
    print_var(elemi, elemf, parti, partf, kick2d_TYPE);
    return 1;
}
