#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define normal_quadrupole_TYPE                                  8
#define normal_sextupole_TYPE                                   9
#define normal_octupole_TYPE                                    10
#define normal_decapole_TYPE                                    11
#define normal_dodecapole_TYPE                                  12
#define normal_14pole_TYPE                                      13
#define normal_16pole_TYPE                                      14
#define normal_18pole_TYPE                                      15
#define normal_20pole_TYPE                                      16
#define normal_pole_float_L                                     0
#define normal_pole_float_TiltComponentCos                      1
#define normal_pole_float_TiltComponentSin                      2
#define normal_pole_float_CurrentEntryDisplacementX             3
#define normal_pole_float_CurrentEntryDisplacementY             4

#define make_map_normal_pole(NAME,i)                                                                                            \
  INT cntnorm##NAME = 0;                                                                                                        \
  extern int normal_##NAME##_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn) {   \
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
    GETATTRF(normal_pole,L);                                                                                                    \
    GETATTRF(normal_pole,TiltComponentCos);                                                                                     \
    GETATTRF(normal_pole,TiltComponentSin);                                                                                     \
    GETATTRF(normal_pole,CurrentEntryDisplacementX);                                                                            \
    GETATTRF(normal_pole,CurrentEntryDisplacementY);                                                                            \
                                                                                                                                \
    RatioPtoPj = One / ( One + ps );                                                                                            \
    xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;         \
    zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin;         \
    crkve = xlvj;                                                                                                               \
    cikve = zlvj;                                                                                                               \
    for( k = 0; k < i ;k++)                                                                                                     \
    {                                                                                                                           \
      crkveuk = crkve * xlvj - cikve * zlvj;                                                                                    \
      cikve = crkve * zlvj + cikve * xlvj;                                                                                      \
      crkve = crkveuk;                                                                                                          \
    }                                                                                                                           \
                                                                                                                                \
    px = px + RatioPtoPj * ( L * TiltComponentCos * crkve + L * TiltComponentSin * cikve );                                     \
    py = py + RatioPtoPj * ( L * TiltComponentSin * crkve - L * TiltComponentCos * cikve );                                     \
    SETCOORDF(partf,px,px);                                                                                                     \
    SETCOORDF(partf,py,py);                                                                                                     \
                                                                                                                                \
    if( cntnorm##NAME++ == 0 ) printf("normal "#NAME" called \n");                                                              \
    return 1;                                                                                                                   \
  }                                                                                                                             \

make_map_normal_pole( quadrupole, 0 );
make_map_normal_pole( sextupole, 1 );
make_map_normal_pole( octupole, 2 );
make_map_normal_pole( decapole, 3 );
make_map_normal_pole( dodecapole, 4 );
make_map_normal_pole( 14pole, 5 );
make_map_normal_pole( 16pole, 6 );
make_map_normal_pole( 18pole, 7 );
make_map_normal_pole( 20pole, 8 );

/*int main(){
  INT elemi[]={0,0}; //mapid,mapst
  FLOAT elemf[]={2.0,0.17,0.45,0.6,0.6};  //L,TiltComponentCos,TiltComponentSin,CurrentEntryDisplacementX,CurrentEntryDisplacementY
  INT parti[]={1,15,0,0,0}; // partn,ndf,ndi,psf,psi
  FLOAT partf[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //p0,beta0,gamma0,m0,E0,x,px,y,py,ct,dp,pt,s,m,q
  INT elemid=0;
  INT partid=0;
  INT partn=0;
  printf("%d\n", normal_sextupole_map(elemi,elemf,elemid,parti,partf,partid,partn));
  return 1;
}*/