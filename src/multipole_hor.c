#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define multipole_TYPE                                          26
#define multipole_float_Knl                                     0
#define multipole_float_Ksl                                     1
#define multipole_float_Hxl                                     2
#define multipole_float_Hyl                                     3
#define multipole_float_L                                       4
#define multipole_float_Rel                                     5

inline void multipole_zapprox_calc(INT pfstart, FLOAT x, FLOAT y, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT ds, FLOAT RatioDeltaPtoPj1, FLOAT RatioBetaToBetaj, FLOAT L, FLOAT TiltComponentCos, FLOAT TiltComponentSin, FLOAT CurrentEntryDisplacementX, FLOAT CurrentEntryDisplacementY, FLOAT HorizontalBendingKick, FLOAT partf[]){
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

#define make_map_multipole_approx(NAME)                                                                                                                                                                                                                     \
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
            GETATTRF(multipole,L);                                                                                                                                                                                                                          \
            GETATTRF(multipole,TiltComponentCos);                                                                                                                                                                                                           \
            GETATTRF(multipole,TiltComponentSin);                                                                                                                                                                                                           \
            GETATTRF(multipole,CurrentEntryDisplacementX);                                                                                                                                                                                                  \
            GETATTRF(multipole,CurrentEntryDisplacementY);                                                                                                                                                                                                  \
            GETATTRF(multipole,HorizontalBendingKick);                                                                                                                                                                                                      \
            GETATTRI(multipole,ApproxType);                                                                                                                                                                                                                 \
                                                                                                                                                                                                                                                                \
            RatioPtoPj = One / ( One + ps );                                                                                                                                                                                                                    \
            RatioDeltaPtoPj1 = ( ps * OnePoweredTo3 ) * RatioPtoPj;                                                                                                                                                                                             \
            MomentumOfParticle = p0 * ( One + ps );                                                                                                                                                                                                             \
            EnergyOfParticle = sqrt( MomentumOfParticle * MomentumOfParticle + m0 * m0 );                                                                                                                                                                       \
            RatioBetaToBetaj = ( EnergyOfParticle * p0 ) / ( E0 * MomentumOfParticle );                                                                                                                                                                         \
                                                                                                                                                                                                                                                                \
            switch(ApproxType){                                                                                                                                                                                                                                 \
                  case 0: multipole_zapprox_calc(pfstart,x,y,px,py,RatioPtoPj,ds,RatioDeltaPtoPj1,RatioBetaToBetaj,L,TiltComponentCos,TiltComponentSin,CurrentEntryDisplacementX,CurrentEntryDisplacementY,HorizontalBendingKick,partf);                    \
                          if( cntmulhorz##NAME++ == 0 ) printf("mulipole horizontal Zero approx "#NAME" called \n");                                                                                                                                            \
                          break;                                                                                                                                                                                                                                \
                  case 1: multipole_nzapprox_calc(pfstart,x,y,px,py,RatioPtoPj,ds,RatioDeltaPtoPj1,RatioBetaToBetaj,L,TiltComponentCos,TiltComponentSin,CurrentEntryDisplacementX,CurrentEntryDisplacementY,HorizontalBendingKick,partf);                   \
                          if( cntmulhorz##NAME++ == 0 ) printf("mulipole horizontal non-Zero approx "#NAME" called \n");                                                                                                                                        \
                          break;                                                                                                                                                                                                                                \
            }                                                                                                                                                                                                                                                   \
                                                                                                                                                                                                                                                                \
            return 1;                                                                                                                                                                                                                                           \
}                                                                                                                                                                                                                                                               \

make_map_multipole_approx(hor_approx_ho);
make_map_multipole_approx(purehor_approx);