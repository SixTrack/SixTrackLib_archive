#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

inline void multipole_hor_nzapprox_calc(INT pfstart, FLOAT x, FLOAT y, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT ds, FLOAT RatioDeltaPtoPj, FLOAT RatioDeltaPtoPj1, FLOAT RatioBetaToBetaj, FLOAT L, FLOAT TiltComponentCos, FLOAT TiltComponentSin, FLOAT CurrentEntryDisplacementX, FLOAT CurrentEntryDisplacementY, FLOAT HorizontalBendingKick, FLOAT partf[]){
      FLOAT xlvj, zlvj;
      xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin; \
      zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin; \
      px = ( px - ((( L * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentCos ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos );                                \
      py = ( py - ((( L * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentSin ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) *  TiltComponentSin;                                         \
      ds = ds + ( RatioBetaToBetaj * HorizontalBendingKick ) * xlvj;                                 \
      
      SETCOORDF(partf,px,px);
      SETCOORDF(partf,py,py);
      SETCOORDF(partf,ds,ds);
}

inline void multipole_hor_zapprox_calc(INT pfstart, FLOAT x, FLOAT y, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT ds, FLOAT RatioDeltaPtoPj, FLOAT RatioDeltaPtoPj1, FLOAT RatioBetaToBetaj, FLOAT L, FLOAT TiltComponentCos, FLOAT TiltComponentSin, FLOAT CurrentEntryDisplacementX, FLOAT CurrentEntryDisplacementY, FLOAT HorizontalBendingKick, FLOAT partf[]){
      FLOAT xlvj, zlvj;
      xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
      zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
      px = ( px - L * TiltComponentSin * RatioDeltaPtoPj1 ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) * TiltComponentSin;
      py = ( py + L * TiltComponentCos * RatioDeltaPtoPj1 ) - (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos);
      ds = ds - ( RatioBetaToBetaj * HorizontalBendingKick ) * zlvj;

      SETCOORDF(partf,px,px);
      SETCOORDF(partf,py,py);
      SETCOORDF(partf,ds,ds);
}

#define make_map_multipole_hor_approx(NAME)                                                                                                                                                                                                                     \
      INT multipole_##NAME##_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){                                                                                                                                    \
            int cntmulhorz##NAME = 0;                                                                                                                                                                                                                           \
            ELEMINIT;                                                                                                                                                                                                                                           \
            INITPARTF;                                                                                                                                                                                                                                          \
            GETCOORDF(partf,x);                                                                                                                                                                                                                                 \
            GETCOORDF(partf,y);                                                                                                                                                                                                                                 \
            GETCOORDF(partf,px);                                                                                                                                                                                                                                \
            GETCOORDF(partf,py);                                                                                                                                                                                                                                \
            GETCOORDF(partf,RatioPtoPj);                                                                                                                                                                                                                        \
            GETCOORDF(partf,ds);                                                                                                                                                                                                                                \
            GETCOORDF(partf,RatioDeltaPtoPj);                                                                                                                                                                                                                   \
            GETCOORDF(partf,RatioDeltaPtoPj1);                                                                                                                                                                                                                  \
            GETCOORDF(partf,RatioBetaToBetaj);                                                                                                                                                                                                                  \
                                                                                                                                                                                                                                                                \
            GETATTRF(multipole_hor,L);                                                                                                                                                                                                                          \
            GETATTRF(multipole_hor,TiltComponentCos);                                                                                                                                                                                                           \
            GETATTRF(multipole_hor,TiltComponentSin);                                                                                                                                                                                                           \
            GETATTRF(multipole_hor,CurrentEntryDisplacementX);                                                                                                                                                                                                  \
            GETATTRF(multipole_hor,CurrentEntryDisplacementY);                                                                                                                                                                                                  \
            GETATTRF(multipole_hor,HorizontalBendingKick);                                                                                                                                                                                                        \
            GETATTRI(multipole_hor,ApproxType);                                                                                                                                                                                                               \
                                                                                                                                                                                                                                                                \
            switch(ApproxType){                                                                                                                                                                                                                                 \
                  case 0: multipole_hor_zapprox_calc(pfstart,x,y,px,py,RatioPtoPj,ds,RatioDeltaPtoPj,RatioDeltaPtoPj1,RatioBetaToBetaj,L,TiltComponentCos,TiltComponentSin,CurrentEntryDisplacementX,CurrentEntryDisplacementY,HorizontalBendingKick,partf);      \
                          if( cntmulhorz##NAME++ == 0 ) printf("mulipole horizontal Zero approx "#NAME" called \n");                                                                                                                                               \
                          break;                                                                                                                                                                                                                                \
                  case 1: multipole_hor_nzapprox_calc(pfstart,x,y,px,py,RatioPtoPj,ds,RatioDeltaPtoPj,RatioDeltaPtoPj1,RatioBetaToBetaj,L,TiltComponentCos,TiltComponentSin,CurrentEntryDisplacementX,CurrentEntryDisplacementY,HorizontalBendingKick,partf);     \
                          if( cntmulhorz##NAME++ == 0 ) printf("mulipole horizontal non-Zero approx "#NAME" called \n");                                                                                                                                           \
                          break;                                                                                                                                                                                                                                \
            }                                                                                                                                                                                                                                                   \
                                                                                                                                                                                                                                                                \
            return 1;                                                                                                                                                                                                                                           \
}                                                                                                                                                                                                                                                               \

make_map_multipole_hor_approx(hor_approx_ho);
make_map_multipole_hor_approx(purehor_approx);

int main(){
  INT elemi[]={0,0,0}; //mapid,mapst,ApproxType
  FLOAT elemf[]={2.0,0.17,0.45,0.6,0.6,1.0};  //L,TiltComponentCos,TiltComponentSin,CurrentEntryDisplacementX,CurrentEntryDisplacementY,HorizontalBendingKick
  INT parti[]={1,15,0,0,0}; // partn,ndf,ndi,psf,psi
  FLOAT partf[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //p0,beta0,gamma0,m0,E0,x,px,y,py,ct,dp,pt,s,m,q
  INT elemid=0;
  INT partid=0;
  INT partn=0;
  printf("%d\n", multipole_purehor_approx_map(elemi,elemf,elemid,parti,partf,partid,partn));
  return 1;
}