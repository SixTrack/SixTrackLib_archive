#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

#define ndimf 2

INT rot2d_init(INT elemi[], FLOAT elemf[], INT elemid){
    FLOAT angle;
    INT elem_floatid;
    elem_floatid=elemi[elemid+1];
    angle=elemf[elem_floatid];
    elemf[elem_floatid+1]=cos(angle);
    elemf[elem_floatid+2]=sin(angle);
    return 1;
} 


INT map_rot2d(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    FLOAT cx,sx,x,y;
    INT elem_floatid,ndf,stf;
    elem_floatid=elemi[elemid+1];
    cx=elemf[elem_floatid+1]; 
    sx=elemf[elem_floatid+2];
    ndf=parti[1];            
    stf=parti[3];            
    x=partf[stf+partid*ndf]; 
    y=partf[stf+partid*ndf+1];
    partf[stf+partid*ndf]= cx*x+sx*y;
    partf[stf+partid*ndf+1]=-sx*x+cx*y;
    return 1;
}

make_map(rot2d,2);

INT map_mul_rot2d(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT idx;
    FLOAT cx,sx,x,y;
    INT elem_floatid;
    elem_floatid=elemi[elemid+1];
    cx=elemf[elem_floatid+1]; 
    sx=elemf[elem_floatid+2];
    for(idx=0;idx<partn;idx++){    
        x=partf[partid+idx*ndimf]; 
        y=partf[partid+idx*ndimf+1];
        partf[partid+idx*ndimf]= cx*x+sx*y;
        partf[partid+idx*ndimf+1]=-sx*x+cx*y;
    }
    return 1;
}

make_vecmap(rot2d,2);

INT map_kcuda_rot2d(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    //to be completed
    return 1;
}


INT map_kopencl_rot2d(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    //to be completed
    return 1;
}

/*
elemi: {}
elemf: {}
parti: {}
partf: {npatf,ndf,ndi,stf,sti}
*/

//for checking
int main(){
    INT elemi[] = {0, 1, 0, 4, 4, 2, 3, 9, 2, 9, 2, 4, 14, 3, 14, 3, 5, 0, 10, 1};
    FLOAT elemf[] = {2.0734511513692637, -0.48175367410171543, 0.8763066800438635, 0.02, 0.01};
    INT elemid = 0;
    INT partid = 0;
    INT parti[] = {1,2,0,0,0};
    FLOAT partf[] = {1,1};
    printf("%d\n", map_vec_rot2d(elemi, elemf, elemid, parti, partf, partid));   
    printf("%d\n", map_vec_mul_rot2d(elemi, elemf, elemid, parti, partf, partid, 0));
    return 0;
}