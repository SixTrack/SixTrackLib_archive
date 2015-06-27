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

inline void drift_exact_calc(INT pfstart, FLOAT beta0, FLOAT x, FLOAT px, FLOAT y, FLOAT py, FLOAT ds, FLOAT ps, FLOAT s, FLOAT L, FLOAT partf[]){
    double Pz;

    Pz = sqrt( beta0*beta0*ps*ps + 2*ps - px*px - py*py +1);
    x += L * ( px / Pz );
    y += L * ( py / Pz );
    ds += L * (((Pz - 1) - beta0*beta0*ps) / Pz );
    s += L;

    SETCOORDF(partf,x,x);
    SETCOORDF(partf,x,y);
    SETCOORDF(partf,ds,ds);
    SETCOORDF(partf,s,s);
}

INT drift_exact_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    // INT cntexactdrift=0;
    ELEMINIT;
    INITPARTF;
    GETCOORDF(partf,x);
    GETCOORDF(partf,y);
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,ds);
    GETCOORDF(partf,ps);
    GETCOORDF(partf,s);
    GETCOORDF(partf,beta0);
    GETATTRF(drift_exact,L);
    drift_exact_calc(pfstart, beta0, x, px, y, py, ds, ps, s, L, GETPARTF(partid));
    print_var(elemi, elemf, parti, partf, drift_exact_TYPE);
    // if( cntexactdrift++ == 0 ) printf("thin6d exact drift \n");
    return 1;
}