#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

INT rot2d_init(INT elemi[], FLOAT elemf[], INT elemid){
    FLOAT angle;
    INT elem_floatid;
    elem_floatid=elemi[elemid+1];
    angle=elemf[elem_floatid];
    elemf[elem_floatid+1]=cos(angle);
    elemf[elem_floatid+2]=sin(angle);
    return 1;
}

inline void calc_rot2d(FLOAT cx, FLOAT sx, FLOAT partf[]){
   FLOAT x=partf[0];
   FLOAT y=partf[1];
   partf[0]= cx*x+sx*y;
   partf[1]=-sx*x+cx*y;
}

INT rot2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    FLOAT cx,sx;
    INT elem_floatid,ndf,stf;
    elem_floatid=elemi[elemid+1];
    ndf=parti[1]; //n of flaot coordinates
    stf=parti[3]; //starot for float coordinates
    cx=elemf[elem_floatid+1];
    sx=elemf[elem_floatid+2];
    calc_rot2d(cx,sx,&partf[stf+partid*ndf]);
    return 1;
}

MAKE_MAPSET(rot2d);

/*
INT map_kcuda_rot2d(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    //to be completed
    return 1;
}


INT map_kopencl_rot2d(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    //to be completed
    return 1;
}
*/

/*
elemi: {mapid, mapst, attr1, attr..., mapid, mapst}
elemf: {attr1,attr...,attr1,attr...,}
parti: {npart,ndf,ndi,stf,sti}
partf: {const1,....,coord1,...,coord<ndf>,coord1,....,coord<ndf>}
*/

//for checking
#define PI (3.141592653589793)

int main(){
    INT elemi[] = {0, 0,
                   0, 4,
                   0, 8};
    FLOAT elemf[] = { PI/2,0,0,
                     -PI/2,0,0,
                      PI/3,0,0};
    INT elemid = 0;
    INT parti[] = {1,2,0,0,0};
    FLOAT partf[] = {1,1};
    INT npart=parti[0];
    INT partid = 0;
    rot2d_init(elemi, elemf, elemid);
    printf("%d\n", rot2d_mapset(elemi, elemf, elemid,
                                parti, partf, partid, npart));
    return 0;
}
