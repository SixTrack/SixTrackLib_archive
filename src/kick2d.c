#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

INT kick2d_init(INT elemi[], FLOAT elemf[], INT elemid){
    return 1;
}

inline void kick2d_calc(FLOAT kv, INT ord, FLOAT partf[]){
   partf[1]+=kv*pow(partf[0],ord);
}

INT kick2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    FLOAT kv;
    INT elem_floatid,ndf,stf,ord;
    elem_floatid=elemi[elemid+1];
    ndf=parti[1]; 
    stf=parti[3]; 
    ord=elemi[elemid+2];
    kv=elemf[elem_floatid+1];
    kick2d_calc(kv,ord,&partf[stf+partid*ndf]);
    return 1;
}

MAKE_MAPSET(kick2d);

/*
INT map_kcuda_kick2d(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    //to be completed
    return 1;
}


INT map_kopencl_kick2d(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
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

void print_var(INT elemi[], FLOAT elemf[], INT parti[], FLOAT partf[]){
    INT i;

    printf("elemi: {");
    for(i=0;i<8;i++){
        printf("%d, ",elemi[i]);
    }
    printf("%d}\n",elemi[i]);

    printf("elemf: {");
    for(i=0;i<2;i++){
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

#define PI (3.141592653589793)

int main(){
    INT elemi[] = {0, 0, 2,
                   0, 4, 4,
                   0, 8, 6};
    FLOAT elemf[] = { 0.03,
                      0.01,
                      0.2};
    INT elemid = 0;
    INT parti[] = {1,2,0,0,0};
    FLOAT partf[] = {1,1};
    INT npart=parti[0];
    INT partid = 0;
    // printf("|%d|%d|%d|%d|\n",(sizeof(elemi)/sizeof(INT)),sizeof(elemf),sizeof(parti),sizeof(partf));
    kick2d_init(elemi, elemf, elemid);
    print_var(elemi, elemf, parti, partf);
    printf("%d\n", kick2d_mapset(elemi, elemf, elemid,
                                parti, partf, partid, npart));
    print_var(elemi, elemf, parti, partf);
    return 0;
}
