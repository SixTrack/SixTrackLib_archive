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

inline void vertical_dipole_calc(INT pfstart, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT L, FLOAT TiltComponentSin, FLOAT TiltComponentCos, FLOAT partf[]){
    px = px - L * TiltComponentSin * RatioPtoPj;
    py = py + L * TiltComponentCos * RatioPtoPj;
    SETCOORDF(partf,px,px);
    SETCOORDF(partf,py,py);
}

INT vertical_dipole_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    // INT cntverdip=0;
    FLOAT RatioPtoPj;
    ELEMINIT;
    INITPARTF;
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,ps);
    GETATTRF(vertical_dipole,L);
    GETATTRF(vertical_dipole,TiltComponentCos);
    GETATTRF(vertical_dipole,TiltComponentSin);
    RatioPtoPj = One / ( One + ps );
    vertical_dipole_calc(pfstart, px, py, RatioPtoPj, L, TiltComponentSin, TiltComponentSin, GETPARTF(partid));
    print_var(elemi, elemf, parti, partf, vertical_dipole_TYPE);
    // if(cntverdip++ ==0) printf("vertical dipole called\n");
    return 1;
}