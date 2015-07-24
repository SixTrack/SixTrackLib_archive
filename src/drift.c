#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define drift_TYPE                                        5
#define drift_float_L                                     0

inline void drift_track(FLOAT beta0, FLOAT x, FLOAT px, FLOAT y, FLOAT py,
                FLOAT tau, FLOAT delta, FLOAT pt, FLOAT s, FLOAT L, FLOAT coordf[]){
    
    FLOAT opdi,beta0i,bbb,xp,yp;

    opdi = 1 / (1 + delta);
    beta0i = L/beta0;
    bbb = (beta0i + pt*L) * opdi;
    xp = px * opdi;
    yp = py * opdi;

    x = x + xp * L;
    y = y + yp * L;
    tau = tau + beta0i - bbb * (1 + ( xp*xp + yp*yp ) / 2);
    s = s + L;

    SETCOORDF(coordf,x,x);
    SETCOORDF(coordf,x,y);
    SETCOORDF(coordf,tau,tau);
    SETCOORDF(coordf,s,s);
}

INT drift_single(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    // INT cntexactdrift=0;
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
    // if( cntexactdrift++ == 0 ) printf("thin6d exact drift \n");
    return 1;
}

INT drift_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    // INT cntexactdrift=0;
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
    // if( cntexactdrift++ == 0 ) printf("thin6d exact drift \n");
    return 1;
}