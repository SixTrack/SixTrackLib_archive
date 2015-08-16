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
    // printf("c beta0i: %23.17e\nc pt: %23.16e\nc betai: %23.16e\nc opdi: %23.16e\nc L: %23.16e\n", beta0i,pt,betai,opdi,L);
    // printf("c pt*L: %23.17e\nc beta0i + pt*L: %23.17e\n", pt*L, (beta0i + pt*L));
    xp = px * opdi;
    yp = py * opdi;

    x = x + xp * L;
    y = y + yp * L;
    // printf("", tau);
    tau = tau + beta0i - betai * (1 + ( xp*xp + yp*yp ) / 2);
    // printf("c betai: %23.16e\nc taua: %23.16e\n", betai, betai * (1 + ( xp*xp + yp*yp ) / 2));
    s = s + L;
    printf("c s: %23.16e\n", s);
    SETCOORDF(coordf,x,x);
    SETCOORDF(coordf,y,y);
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
    print_var(elemi,elemf,parti,partf,drift_TYPE);
    // if( cntexactdrift++ == 0 ) printf("thin6d exact drift \n");
    return 1;
}