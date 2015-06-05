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

inline void kick2d_calc(INT i, INT j, FLOAT k, INT o, FLOAT partf[]){
   partf[j]+=k*pow(partf[i],o);
}

INT kick2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    FLOAT k;
    INT elem_floatid,ndf,stf,o,i,j;
    elem_floatid=elemi[elemid+1];
    ndf=parti[1]; 
    stf=parti[3]; 
    o=elemi[elemid+2];
    k=elemf[elem_floatid+1];
    i=stf+partid*ndf;
    j=stf+partid*ndf+1;
    for(partid=0;partid<partn;partid++){
      kick2d_calc(i,j,k,o,partf);
    };
    return 1;
}


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
void print_var_kick(INT elemi[], FLOAT elemf[], INT parti[], FLOAT partf[]){
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