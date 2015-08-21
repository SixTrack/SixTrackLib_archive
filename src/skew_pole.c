#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define skew_quadrupole_TYPE                                    17
#define skew_sextupole_TYPE                                     18
#define skew_octupole_TYPE                                      19
#define skew_decapole_TYPE                                      20
#define skew_dodecapole_TYPE                                    21
#define skew_14pole_TYPE                                        22
#define skew_16pole_TYPE                                        23
#define skew_18pole_TYPE                                        24
#define skew_20pole_TYPE                                        25
#define skew_pole_float_L                                       0
#define skew_pole_float_TiltComponentCos                        1
#define skew_pole_float_TiltComponentSin                        2
#define skew_pole_float_CurrentEntryDisplacementX               3
#define skew_pole_float_CurrentEntryDisplacementY               4

#define make_map_skew_pole(NAME,i)                                                                                              \
  INT cntskew##NAME = 0;                                                                                                        \
  extern int skew_##NAME##_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn) {     \
    FLOAT RatioPtoPj;                                                                                                           \
    FLOAT xlvj, zlvj;                                                                                                           \
    FLOAT crkve, cikve, crkveuk;                                                                                                \
    INT k = 0;                                                                                                                  \
    ELEMINIT;                                                                                                                   \
    INITPARTF;                                                                                                                  \
    GETCOORDF(partf,x);                                                                                                         \
    GETCOORDF(partf,y);                                                                                                         \
    GETCOORDF(partf,px);                                                                                                        \
    GETCOORDF(partf,py);                                                                                                        \
    GETCOORDF(partf,ps);                                                                                                        \
    GETATTRF(skew_pole,L);                                                                                                      \
    GETATTRF(skew_pole,TiltComponentCos);                                                                                       \
    GETATTRF(skew_pole,TiltComponentSin);                                                                                       \
    GETATTRF(skew_pole,CurrentEntryDisplacementX);                                                                              \
    GETATTRF(skew_pole,CurrentEntryDisplacementY);                                                                              \
                                                                                                                                \
    RatioPtoPj = One / ( One + ps );                                                                                            \
    xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;         \
    zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;         \
    crkve = xlvj;                                                                                                               \
    cikve = zlvj;                                                                                                               \
    for( k = 0; k < i ;k++)                                                                                                     \
    {                                                                                                                           \
      crkveuk = crkve * xlvj - cikve * zlvj;                                                                                    \
      cikve = crkve * zlvj + cikve * xlvj;                                                                                      \
      crkve = crkveuk;                                                                                                          \
    }                                                                                                                           \
                                                                                                                                \
    px = px + RatioPtoPj * ( L * TiltComponentCos * cikve - L * TiltComponentSin * crkve );                                     \
    py = py + RatioPtoPj * ( L * TiltComponentCos * crkve - L * TiltComponentSin * cikve );                                     \
    SETCOORDF(partf,px,px);                                                                                                     \
    SETCOORDF(partf,py,py);                                                                                                     \
                                                                                                                                \
    if( cntskew##NAME++ == 0 ) printf("skew "#NAME" called \n");                                                                \
    return 1;                                                                                                                   \
  }                                                                                                                             \

make_map_skew_pole( quadrupole, 0 );
make_map_skew_pole( sextupole, 1 );
make_map_skew_pole( octupole, 2 );
make_map_skew_pole( decapole, 3 );
make_map_skew_pole( dodecapole, 4 );
make_map_skew_pole( 14pole, 5 );
make_map_skew_pole( 16pole, 6 );
make_map_skew_pole( 18pole, 7 );
make_map_skew_pole( 20pole, 8 );