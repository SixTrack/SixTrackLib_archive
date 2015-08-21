#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define drift_TYPE                                        5
#define drift_float_L                                     0

void print_var(INT [], FLOAT [], INT [], FLOAT [], INT );

inline void drift_track(FLOAT beta0, FLOAT x, FLOAT px, FLOAT y, FLOAT py,
                FLOAT tau, FLOAT delta, FLOAT pt, FLOAT s, FLOAT L, FLOAT coordf[]){
    
    FLOAT opdi,beta0i,betai,xp,yp;

    opdi = 1 / (1 + delta);
    beta0i = L/beta0;
    betai = (beta0i + pt*L) * opdi;
    xp = px * opdi;
    yp = py * opdi;

    x = x + xp * L;
    y = y + yp * L;
    tau = tau + beta0i - betai * (1 + ( xp*xp + yp*yp ) / 2);
    s = s + L;
    SETCOORDF(coordf,x,x);
    SETCOORDF(coordf,y,y);
    SETCOORDF(coordf,tau,tau);
    SETCOORDF(coordf,s,s);
}

INT drift_single(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
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
    GETATTRF(drift,L);
    drift_track(beta0, x, px, y, py, tau, delta, pt, s, L, GETPARTF(partid));
    return 1;
}

INT drift_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
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
    GETATTRF(drift,L);
    for(;partid<partn;partid++){
      drift_track(beta0, x, px, y, py, tau, delta, pt, s, L, GETPARTF(partid));
    };
    print_var(elemi,elemf,parti,partf,drift_TYPE);
    return 1;
}