#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define cavity_TYPE                                          8
#define cavity_float_Vn                                      0
#define cavity_float_Freq                                    1
#define cavity_float_Lag                                     2
#define cavity_float_S0                                      3

inline void cavity_track(INT partid, INT stf, INT ndf, FLOAT beta0, FLOAT tau, FLOAT pt, FLOAT chi,
                FLOAT s, FLOAT Vn, FLOAT Freq, FLOAT Lag, FLOAT S0, FLOAT coordf[]){

    FLOAT k,phase;

    k = Freq / Clight;
    phase = Lag - k * tau;
    if(S0 >= 0)
        phase = phase + k * (s - S0) / beta0;

    pt = pt + chi * Vn * sin( 2*M_PI*phase);

    SETCOORDF(coordf,pt,pt);
}

INT cavity_single(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    INITPARTF;

    GETATTRF(cavity,Vn);
    GETATTRF(cavity,Freq);
    GETATTRF(cavity,Lag);
    GETATTRF(cavity,S0);

    GETCONSTF(partf,beta0);
    GETCOORDF(partf,tau);
    GETCOORDF(partf,pt);
    GETCOORDF(partf,chi);
    GETCOORDF(partf,s);

    cavity_calc(partid, stf, ndf, beta0, tau, pt, chi, s, Vn, Freq, Lag, S0, GETPARTF(partid));
    return 1;
}

INT cavity_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    INITPARTF;

    GETATTRF(cavity,Vn);
    GETATTRF(cavity,Freq);
    GETATTRF(cavity,Lag);
    GETATTRF(cavity,S0);

    GETCONSTF(partf,beta0);
    GETCOORDF(partf,tau);
    GETCOORDF(partf,pt);
    GETCOORDF(partf,chi);
    GETCOORDF(partf,s);
    for(;partid<partn;partid++){
      cavity_calc(partid, stf, ndf, beta0, tau, pt, chi, s, Vn, Freq, Lag, S0, GETPARTF(partid));
    };
    return 1;
}