#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define drift_exact_TYPE                                        6
#define drift_exact_float_L                                     0

void print_var(INT [], FLOAT [], INT [], FLOAT [], INT );

inline void drift_exact_track(FLOAT beta0, FLOAT x, FLOAT px, FLOAT y, FLOAT py,
                FLOAT tau, FLOAT delta, FLOAT pt, FLOAT s, FLOAT L, FLOAT coordf[]){
    
    FLOAT pzi,bzi,xp,yp;

    pzi = L / (sqrt((1+delta)*(1 + delta) - px*px - py*py ));
    bzi = (1/beta0 + pt)*pzi;
    xp = px * pzi;
    yp = py * pzi;
    printf("C pzi: %23.16e bzi: %23.16e xp: %23.16e yp: %23.16e\n", pzi,bzi,xp,yp);
    x = x + xp;
    y = y + yp;
    tau = tau + L/beta0 - bzi;
    s = s + L;

    SETCOORDF(coordf,x,x);
    SETCOORDF(coordf,y,y);
    SETCOORDF(coordf,tau,tau);
    SETCOORDF(coordf,s,s);
}

INT drift_exact_single(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    INITPARTF;
    GETCOORDF(partf,x);
    GETCOORDF(partf,y);
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,tau);
    GETCOORDF(partf,delta);
    GETCOORDF(partf,pt);
    GETCOORDF(partf,s);
    GETCONSTF(partf,beta0);
    GETATTRF(drift_exact,L);
    drift_exact_track(beta0, x, px, y, py, tau, delta, pt, s, L, GETPARTF(partid));
    return 1;
}

INT drift_exact_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    INITPARTF;
    GETCOORDF(partf,x);
    GETCOORDF(partf,y);
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,tau);
    GETCOORDF(partf,delta);
    GETCOORDF(partf,pt);
    GETCOORDF(partf,s);
    GETCONSTF(partf,beta0);
    GETATTRF(drift_exact,L);
    for(;partid<partn;partid++){
      drift_exact_track(beta0, x, px, y, py, tau, delta, pt, s, L, GETPARTF(partid));
    };
    print_var(elemi,elemf,parti,partf,drift_exact_TYPE);
    return 1;
}

