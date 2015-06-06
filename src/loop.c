#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

#define rot2d_TYPE 0
#define kick2d_TYPE 1
#define counter_TYPE 2

INT rot2d_init(INT elemi[], FLOAT elemf[], INT elemid);
INT rot2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn);
INT kick2d_init(INT elemi[], FLOAT elemf[], INT elemid);
INT kick2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn);
INT counter_init(INT elemi[], FLOAT elemf[], INT elemid);
INT counter_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn);

INT loop_init(INT elemi[], FLOAT elemf[], INT elemid){
    return 1;
}

inline void loop_calc(INT i, INT j, FLOAT cx, FLOAT sx, FLOAT partf[]){
}

INT loop_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT nelem,mapid,i,retval=1;
    INT *elems;
    nelem=elemi[2];
    elems=malloc(nelem*sizeof(INT));
    for(i=0;i<nelem;i++)
        elems[i]=elemi[3+i];
    while(retval>0){ 
        for(i=0;i<nelem;i++){
            mapid=elemi[elems[i]];
            switch (mapid) {
              case rot2d_TYPE:
                rot2d_init(elemi, elemf, elems[i]);
                retval=rot2d_map(elemi, elemf, elems[i], parti, partf, partid, partn);
                break;
              case kick2d_TYPE:
                kick2d_init(elemi, elemf, elems[i]);
                retval=kick2d_map(elemi, elemf, elems[i], parti, partf, partid, partn);
                break;
              case counter_TYPE:
                counter_init(elemi, elemf, elems[i]);
                retval=counter_map(elemi, elemf, elems[i], parti, partf, partid, partn);
                break;
            }
        }
    }
    return 1;
}

/*
INT map_kcuda_loop(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    //to be completed
    return 1;
}


INT map_kopencl_loop(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
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
    for(i=0;i<23;i++){
        printf("%d, ",elemi[i]);
    }
    printf("%d}\n",elemi[i]);

    printf("elemf: {");
    for(i=0;i<6;i++){
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
    printf("%f}\n\n",partf[i]);
}