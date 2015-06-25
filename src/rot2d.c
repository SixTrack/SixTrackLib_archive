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

INT rot2d_init(INT elemi[], FLOAT elemf[], INT elemid){
    ELEMINIT;
    GETATTRF(rot2d,angle);
    SETATTRF(rot2d,cx,cos(angle));
    SETATTRF(rot2d,sx,sin(angle));
    return 1;
}

inline void rot2d_calc(INT pfstart, FLOAT cx, FLOAT sx, FLOAT partf[]){
   GETCOORDF(partf,x);
   GETCOORDF(partf,y);
   SETCOORDF(partf,x,cx*x+sx*y);
   SETCOORDF(partf,y,-sx*x+cx*y);
}

INT rot2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    GETATTRF(rot2d,cx);
    GETATTRF(rot2d,sx);
    GETATTRI(rot2d,i);
    GETATTRI(rot2d,j);
    INITPARTF;
    for(partid=0;partid<partn;partid++){
      rot2d_calc(pfstart,cx,sx,GETPARTF(partid));
    };
    print_var(elemi, elemf, parti, partf, rot2d_TYPE);
    return 1;
}