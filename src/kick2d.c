#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define kick2d_TYPE 1
#define kick2d_float_k 0
#define kick2d_int_o 0
#define kick2d_int_i 1
#define kick2d_int_j 2

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
    for(;partid<partn;partid++){
      kick2d_calc(i,j,k,o,GETPARTF(partid));
    };
    return 1;
}
