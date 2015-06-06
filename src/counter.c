#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

void print_var(INT elemi[], FLOAT elemf[], INT parti[], FLOAT partf[]);

INT counter_init(INT elemi[], FLOAT elemf[], INT elemid){    
    return 1;
}

inline void counter_calc(INT *retval, INT count, INT count_max, FLOAT partf[]){
    if (count<count_max){
        *retval=1;
    } 
    else{
        *retval=-1;
    }
} 

INT counter_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT ndf,stf,count,count_max,retval=-1;
    ndf=parti[1];
    stf=parti[3];
    count_max=elemi[elemid+2];
    count=elemi[elemid+3]++;
    counter_calc(&retval,count,count_max,&partf[stf+partid*ndf]);
    printf("COUNTER:\n");
    print_var(elemi, elemf, parti, partf);
    return retval;
}

/*
INT map_kcuda_counter(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    //to be completed
    return 1;
}


INT map_kopencl_counter(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
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