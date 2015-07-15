#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define rot2d_TYPE                                              0
#define rot2d_float_angle                                       0
#define rot2d_float_cx                                          1
#define rot2d_float_sx                                          2
#define rot2d_int_i                                             0
#define rot2d_int_j                                             1

INT rot2d_init(INT elemi[], FLOAT elemf[], INT elemid){
    FLOAT angle_rad;
    ELEMINIT;
    GETATTRF(rot2d,angle);
    angle_rad=(2*M_PI)*angle;
    SETATTRF(rot2d,cx,cos(angle_rad));
    SETATTRF(rot2d,sx,sin(angle_rad));
    return 1;
}

inline void rot2d_calc(INT i, INT j, FLOAT cx, FLOAT sx, FLOAT partf[]){
   FLOAT x=partf[i];
   FLOAT y=partf[j];
   partf[i]= cx*x+sx*y;
   partf[j]=-sx*x+cx*y;
}

INT rot2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    GETATTRF(rot2d,cx);
    GETATTRF(rot2d,sx);
    GETATTRI(rot2d,i);
    GETATTRI(rot2d,j);
    INITPARTF;
    for(;partid<partn;partid++){
      rot2d_calc(i,j,cx,sx,GETPARTF(partid));
    };
    return 1;
}