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
    ndf=parti[1]; //n of flaot coordinates
    stf=parti[3]; //starot for float coordinates
    cx=elemf[elem_floatid+1];
    sx=elemf[elem_floatid+2];
    i=stf+partid*ndf;
    j=stf+partid*ndf+1;
    for(partid=0;partid<partn;partid++){
      rot2d_calc(i,j,cx,sx,partf);
    };
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

//for checking
void print_var_rot(INT elemi[], FLOAT elemf[], INT parti[], FLOAT partf[]){
    INT i;

    printf("elemi: {");
    for(i=0;i<5;i++){
        printf("%d, ",elemi[i]);
    }
    printf("%d}\n",elemi[i]);

    printf("elemf: {");
    for(i=0;i<8;i++){
        printf("%f, ",elemf[i]);
    }
    printf("%f}\n",elemf[i]);

    printf("parti: {");
    for(i=0;i<4;i++){
        printf("%d, ",parti[i]);
    }
    printf("%d}\n", parti[i]);

    printf("partf: {");
    for(i=0;i<1;i++){
        printf("%f, ",partf[i]);
    }
    printf("%f}\n",partf[i]);
}