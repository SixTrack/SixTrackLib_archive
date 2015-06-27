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

inline void horizontal_dipole_calc(INT pfstart, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT L, FLOAT TiltComponentSin, FLOAT TiltComponentCos, FLOAT partf[]){
    px = px - L * TiltComponentCos * RatioPtoPj;
    py = py + L * TiltComponentSin * RatioPtoPj;
    SETCOORDF(partf,px,px);
    SETCOORDF(partf,py,py);
}

INT horizontal_dipole_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT cnthordipole=0;
    ELEMINIT;
    INITPARTF;    
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,RatioPtoPj)
    GETATTRF(horizontal_dipole,L);
    GETATTRF(horizontal_dipole,TiltComponentCos);
    GETATTRF(horizontal_dipole,TiltComponentSin);
    horizontal_dipole_calc(pfstart, px, py, RatioPtoPj, L, TiltComponentSin, TiltComponentSin, GETPARTF(partid));
    if(cnthordipole++ ==0) printf("horizontal dipole called\n");
    return 1;
}

int main(){
  INT elemi[]={0,0}; //mapid,mapst
  FLOAT elemf[]={2.0,0.17,0.45};  //L,TiltComponentCos,TiltComponentSin
  INT parti[]={1,15,0,0,0}; // partn,ndf,ndi,psf,psi
  FLOAT partf[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //p0,beta0,gamma0,m0,E0,x,px,y,py,ct,dp,pt,s,m,q
  INT elemid=0;
  INT partid=0;
  INT partn=0;
  printf("%d\n", horizontal_dipole_map(elemi,elemf,elemid,parti,partf,partid,partn));
  return 1;
}