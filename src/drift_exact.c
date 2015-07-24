#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define drift_exact_TYPE                                        6
#define drift_exact_float_L                                     0

inline void drift_exact_track(FLOAT beta0, FLOAT x, FLOAT px, FLOAT y, FLOAT py,
                FLOAT tau, FLOAT delta, FLOAT pt, FLOAT s, FLOAT L, FLOAT coordf[]){
    
    FLOAT pzi,bzi,xp,yp;

    pzi = L / (sqrt((1+delta)*(1 + delta) - px*px - py*py ));
    bzi = (1/beta0 + pt)*pzi;
    xp = px * pzi;
    yp = py * pzi;

    x = x + xp;
    y = y + yp;
    tau = tau + L/beta0 - bzi;
    s = s + L;

    SETCOORDF(coordf,x,x);
    SETCOORDF(coordf,x,y);
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
    return 1;
}