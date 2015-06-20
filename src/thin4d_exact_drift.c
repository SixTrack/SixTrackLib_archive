#include "sixtrackmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

void print_var(INT [], FLOAT [], INT [], FLOAT [], INT);

inline void thin4d_exact_drift_calc(INT elem_floatid, FLOAT x, FLOAT y, FLOAT px, FLOAT py, FLOAT PhysicalLengthOfBlock, FLOAT partf[]){
    double Pz;
    x *= OnePoweredToMinus3;
    y *= OnePoweredToMinus3;
    px *= OnePoweredToMinus3;
    py *= OnePoweredToMinus3;

    Pz = sqrt( One - ( px * px + py * py ));
    x += PhysicalLengthOfBlock * ( px / Pz );
    y += PhysicalLengthOfBlock * ( py / Pz );

    SETCOORDF(partf,x,x*OnePoweredTo3);
    SETCOORDF(partf,x,px*OnePoweredTo3);
    SETCOORDF(partf,x,y*OnePoweredTo3);
    SETCOORDF(partf,x,py*OnePoweredTo3);
}

INT thin4d_exact_drift_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT cntexactdrift4d;
    ELEMINIT;
    INITPARTF;
    GETCOORDF(partf,x);
    GETCOORDF(partf,y);
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETATTRF(thin4d_exact_drift,PhysicalLengthOfBlock);
    thin4d_exact_drift_calc(elem_floatid, x, y, px, py, PhysicalLengthOfBlock, GETPARTF(partid));
    if( cntexactdrift4d++ == 0 ) printf("thin4d exact drift \n");

    return 1;
}

int main(){
  INT elemi[]={0,0}; //mapid,mapst
  FLOAT elemf[]={2.0};  //PhysicalLengthOfBlock
  INT parti[]={1,15,0,0,0}; // partn,ndf,ndi,psf,psi
  FLOAT partf[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //p0,beta0,gamma0,m0,E0,x,px,y,py,ct,dp,pt,s,m,q
  INT elemid=0;
  INT partid=0;
  INT partn=0;
  printf("%d\n", thin4d_exact_drift_map(elemi,elemf,elemid,parti,partf,partid,partn));
  return 1;
}