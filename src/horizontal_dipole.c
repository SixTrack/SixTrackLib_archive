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
    // INT cnthordipole=0;
    FLOAT RatioPtoPj=0;
    ELEMINIT;
    INITPARTF;    
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,ps);
    GETATTRF(horizontal_dipole,L);
    GETATTRF(horizontal_dipole,TiltComponentCos);
    GETATTRF(horizontal_dipole,TiltComponentSin);
    RatioPtoPj=1/(1+ps);
    horizontal_dipole_calc(pfstart, px, py, RatioPtoPj, L, TiltComponentSin, TiltComponentSin, GETPARTF(partid));
    print_var(elemi, elemf, parti, partf, horizontal_dipole_TYPE);
    // if(cnthordipole++ ==0) printf("horizontal dipole called\n");
    return 1;
}