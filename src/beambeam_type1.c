#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

// void print_var(INT [], FLOAT [], INT [], FLOAT [], INT);

inline void beambeam_type1_calc(){
}

INT beambeam_type1_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT cntbb1=0;
    ELEMINIT;
    INITPARTF;
    GETCOORDF(partf,x);
    GETCOORDF(partf,y);
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,RatioPtoPj);

    GETATTRF(beambeam_type1,HorBeamBeamSeparation);
    GETATTRF(beambeam_type1,VerBeamBeamSeparation);
    GETATTRF(beambeam_type1,L);
    GETATTRF(beambeam_type1,ClosedOrbitBeamX);
    GETATTRF(beambeam_type1,ClosedOrbitBeamY);
    GETATTRF(beambeam_type1,ClosedOrbitBeamSigma);
    GETATTRF(beambeam_type1,ClosedOrbitBeamPx);
    GETATTRF(beambeam_type1,ClosedOrbitBeamPy);
    GETATTRF(beambeam_type1,ClosedOrbitBeamDelta);
    GETATTRF(beambeam_type1,BeamOffsetX);
    GETATTRF(beambeam_type1,BeamOffsetY);
    GETATTRF(beambeam_type1,BeamOffsetSigma);
    GETATTRF(beambeam_type1,BeamOffsetPx);
    GETATTRF(beambeam_type1,BeamOffsetPy);
    GETATTRF(beambeam_type1,BeamOffsetDelta);
    GETATTRF(beambeam_type1,bbcu11);
    GETATTRF(beambeam_type1,bbcu12);
    GETATTRF(beambeam_type1,SigmaNqX);
    GETATTRF(beambeam_type1,SigmaNqY);
    GETATTRF(beambeam_type1,SquareOfSigmaNX);
    GETATTRF(beambeam_type1,SquareOfSigmaNY);
    GETATTRI(beambeam_type1,SwitchToLinearCoupling);



    if( cntbb1++ == 0 ) printf("beam beam 1\n");

    // print_var(elemi, elemf, parti, partf, rot2d_TYPE);
    return 1;
    //NOTE: exp_rn changed to exp
}

int main(){
  INT elemi[]={0,0,2}; //mapid,mapst,SwitchToLinearCoupling
  FLOAT elemf[]={2.0,0.17,0.45,0.6,0.6,0.3,0.4,0.1,1.0,2.0,2.3,12.0,3.2,4.05,3.6,7.12,5.5,9.0,5.2,4.44};  //HorBeamBeamSeparation,VerBeamBeamSeparation,L,ClosedOrbitBeamX,ClosedOrbitBeamY,ClosedOrbitBeamSigma,ClosedOrbitBeamPx,ClosedOrbitBeamPy,ClosedOrbitBeamDelta,BeamOffsetX,BeamOffsetY,BeamOffsetSigma,BeamOffsetPx,BeamOffsetPy,BeamOffsetDelta,bbcu11,bbcu12,SigmaNqX,SigmaNqY,SquareOfSigmaNX,SquareOfSigmaNY         
  INT parti[]={1,15,0,0,0}; // partn,ndf,ndi,psf,psi
  FLOAT partf[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //p0,beta0,gamma0,m0,E0,x,px,y,py,ct,dp,pt,s,m,q
  INT elemid=0;
  INT partid=0;
  INT partn=0;
  printf("%d\n", beambeam_type1_map(elemi,elemf,elemid,parti,partf,partid,partn));
  return 1;
}