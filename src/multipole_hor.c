#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define hor_approx_ho_TYPE                                      26
#define purehor_approx_TYPE                                     27
#define multipole_hor_float_L                                   0
#define multipole_hor_float_TiltComponentCos                    1
#define multipole_hor_float_TiltComponentSin                    2
#define multipole_hor_float_CurrentEntryDisplacementX           3
#define multipole_hor_float_CurrentEntryDisplacementY           4
#define multipole_hor_float_HorizontalBendingKick               5
#define multipole_hor_int_ApproxType                            0

inline void multipole_hor_nzapprox_calc(INT pfstart, FLOAT x, FLOAT y, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT ds, FLOAT RatioDeltaPtoPj1, FLOAT RatioBetaToBetaj, FLOAT L, FLOAT TiltComponentCos, FLOAT TiltComponentSin, FLOAT CurrentEntryDisplacementX, FLOAT CurrentEntryDisplacementY, FLOAT HorizontalBendingKick, FLOAT partf[]){
      FLOAT xlvj, zlvj;
      xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
      zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
      px = ( px - ((( L * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentCos ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos );
      py = ( py - ((( L * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentSin ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) *  TiltComponentSin;
      ds = ds + ( RatioBetaToBetaj * HorizontalBendingKick ) * xlvj;
      
      SETCOORDF(partf,px,px);
      SETCOORDF(partf,py,py);
      SETCOORDF(partf,ds,ds);
}

inline void multipole_hor_zapprox_calc(INT pfstart, FLOAT x, FLOAT y, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT ds, FLOAT RatioDeltaPtoPj1, FLOAT RatioBetaToBetaj, FLOAT L, FLOAT TiltComponentCos, FLOAT TiltComponentSin, FLOAT CurrentEntryDisplacementX, FLOAT CurrentEntryDisplacementY, FLOAT HorizontalBendingKick, FLOAT partf[]){
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
            INT cntmulhorz##NAME = 0;                                                                                                                                                                                                                           \
            FLOAT RatioPtoPj, RatioDeltaPtoPj1, RatioBetaToBetaj, MomentumOfParticle, EnergyOfParticle;                                                                                                                                                         \
            ELEMINIT;                                                                                                                                                                                                                                           \
            INITPARTF;                                                                                                                                                                                                                                          \
            GETCOORDF(partf,x);                                                                                                                                                                                                                                 \
            GETCOORDF(partf,y);                                                                                                                                                                                                                                 \
            GETCOORDF(partf,px);                                                                                                                                                                                                                                \
            GETCOORDF(partf,py);                                                                                                                                                                                                                                \
            GETCOORDF(partf,ps);                                                                                                                                                                                                                                \
            GETCOORDF(partf,ds);                                                                                                                                                                                                                                \
            GETCOORDF(partf,E0);                                                                                                                                                                                                                                \
            GETCOORDF(partf,m0);                                                                                                                                                                                                                                \
            GETCOORDF(partf,p0);                                                                                                                                                                                                                                \
                                                                                                                                                                                                                                                                \
            GETATTRF(multipole_hor,L);                                                                                                                                                                                                                          \
            GETATTRF(multipole_hor,TiltComponentCos);                                                                                                                                                                                                           \
            GETATTRF(multipole_hor,TiltComponentSin);                                                                                                                                                                                                           \
            GETATTRF(multipole_hor,CurrentEntryDisplacementX);                                                                                                                                                                                                  \
            GETATTRF(multipole_hor,CurrentEntryDisplacementY);                                                                                                                                                                                                  \
            GETATTRF(multipole_hor,HorizontalBendingKick);                                                                                                                                                                                                      \
            GETATTRI(multipole_hor,ApproxType);                                                                                                                                                                                                                 \
                                                                                                                                                                                                                                                                \
            RatioPtoPj = One / ( One + ps );                                                                                                                                                                                                                    \
            RatioDeltaPtoPj1 = ( ps * OnePoweredTo3 ) * RatioPtoPj;                                                                                                                                                                                             \
            MomentumOfParticle = p0 * ( One + ps );                                                                                                                                                                                                             \
            EnergyOfParticle = sqrt( MomentumOfParticle * MomentumOfParticle + m0 * m0 );                                                                                                                                                                       \
            RatioBetaToBetaj = ( EnergyOfParticle * p0 ) / ( E0 * MomentumOfParticle );                                                                                                                                                                         \
                                                                                                                                                                                                                                                                \
            switch(ApproxType){                                                                                                                                                                                                                                 \
                  case 0: multipole_hor_zapprox_calc(pfstart,x,y,px,py,RatioPtoPj,ds,RatioDeltaPtoPj1,RatioBetaToBetaj,L,TiltComponentCos,TiltComponentSin,CurrentEntryDisplacementX,CurrentEntryDisplacementY,HorizontalBendingKick,partf);                    \
                          if( cntmulhorz##NAME++ == 0 ) printf("mulipole horizontal Zero approx "#NAME" called \n");                                                                                                                                            \
                          break;                                                                                                                                                                                                                                \
                  case 1: multipole_hor_nzapprox_calc(pfstart,x,y,px,py,RatioPtoPj,ds,RatioDeltaPtoPj1,RatioBetaToBetaj,L,TiltComponentCos,TiltComponentSin,CurrentEntryDisplacementX,CurrentEntryDisplacementY,HorizontalBendingKick,partf);                   \
                          if( cntmulhorz##NAME++ == 0 ) printf("mulipole horizontal non-Zero approx "#NAME" called \n");                                                                                                                                        \
                          break;                                                                                                                                                                                                                                \
            }                                                                                                                                                                                                                                                   \
                                                                                                                                                                                                                                                                \
            return 1;                                                                                                                                                                                                                                           \
}                                                                                                                                                                                                                                                               \

make_map_multipole_hor_approx(hor_approx_ho);
make_map_multipole_hor_approx(purehor_approx);

/*int main(){
  INT elemi[]={0,0,0}; //mapid,mapst,ApproxType
  FLOAT elemf[]={2.0,0.17,0.45,0.6,0.6,1.0};  //L,TiltComponentCos,TiltComponentSin,CurrentEntryDisplacementX,CurrentEntryDisplacementY,HorizontalBendingKick
  INT parti[]={1,15,0,0,0}; // partn,ndf,ndi,psf,psi
  FLOAT partf[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //p0,beta0,gamma0,m0,E0,x,px,y,py,ct,dp,pt,s,m,q
  INT elemid=0;
  INT partid=0;
  INT partn=0;
  printf("%d\n", multipole_purehor_approx_map(elemi,elemf,elemid,parti,partf,partid,partn));
  return 1;
}*/