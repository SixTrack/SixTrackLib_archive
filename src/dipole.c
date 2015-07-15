#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define dipole_TYPE                                             7
#define dipole_float_L                                          0
#define dipole_float_TiltComponentCos                           1
#define dipole_float_TiltComponentSin                           2
#define dipole_int_DipoleType                                   0

inline void horizontal_dipole_calc(INT pfstart, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT L, 
                                    FLOAT TiltComponentSin, FLOAT TiltComponentCos, FLOAT partf[]){
    px = px + L * TiltComponentCos * RatioPtoPj;
    py = py + L * TiltComponentSin * RatioPtoPj;
    SETCOORDF(partf,px,px);
    SETCOORDF(partf,py,py);
}

inline void vertical_dipole_calc(INT pfstart, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT L,
                                    FLOAT TiltComponentSin, FLOAT TiltComponentCos, FLOAT partf[]){
    px = px - L * TiltComponentSin * RatioPtoPj;
    py = py + L * TiltComponentCos * RatioPtoPj;
    SETCOORDF(partf,px,px);
    SETCOORDF(partf,py,py);
}

INT dipole_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    FLOAT RatioPtoPj=0;
    ELEMINIT;
    INITPARTF;    
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,ps);
    GETATTRF(dipole,L);
    GETATTRF(dipole,TiltComponentCos);
    GETATTRF(dipole,TiltComponentSin);
    GETATTRI(dipole,DipoleType);
    RatioPtoPj = One / ( One + ps );
    if(DipoleType==0){
        horizontal_dipole_calc(pfstart, px, py, RatioPtoPj, L, TiltComponentSin, TiltComponentSin, GETPARTF(partid));
    }
    else{
        vertical_dipole_calc(pfstart, px, py, RatioPtoPj, L, TiltComponentSin, TiltComponentSin, GETPARTF(partid));
    }
    return 1;
}