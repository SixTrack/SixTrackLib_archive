#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

void print_var(INT elemi[], FLOAT elemf[], INT parti[], FLOAT partf[]);

INT rot2d_init(INT elemi[], FLOAT elemf[], INT elemid){
    FLOAT angle;
    INT elem_floatid;
    elem_floatid=elemi[elemid+1];
    angle=elemf[elem_floatid];
    elemf[elem_floatid+1]=cos(angle);
    elemf[elem_floatid+2]=sin(angle);
    return 1;
}

inline void rot2d_calc(INT i, INT j, FLOAT cx, FLOAT sx, FLOAT partf[]){
   FLOAT x=partf[i];
   FLOAT y=partf[j];
   partf[i]= cx*x+sx*y;
   partf[j]=-sx*x+cx*y;
}

INT rot2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    FLOAT cx,sx;
    INT elem_floatid,ndf,stf,i,j;
    elem_floatid=elemi[elemid+1];
    ndf=parti[1]; 
    stf=parti[3]; 
    i=elemi[elemid+2];
    j=elemi[elemid+3];
    cx=elemf[elem_floatid+1];
    sx=elemf[elem_floatid+2];
    for(partid=0;partid<partn;partid++){
      rot2d_calc(i,j,cx,sx,&partf[stf+partid*ndf]);
    };
    printf("ROT2D:\n");
    print_var(elemi, elemf, parti, partf);
    return 1;
}

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