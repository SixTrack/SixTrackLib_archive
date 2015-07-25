#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define multipole_TYPE                                          7
#define multipole_int_Knlen                                     0
#define multipole_int_Kslen                                     1
//#define multipole_float_Knl                                     0
//#define multipole_float_Ksl                                     Knlen
#define multipole_float_Hxl                                     Knlen+Kslen
#define multipole_float_Hyl                                     1+Knlen+Kslen
#define multipole_float_L                                       2+Knlen+Kslen
#define multipole_float_Rel                                     3+Knlen+Kslen

void print_var(INT [], FLOAT [], INT [], FLOAT [], INT );

inline void multipole_track(FLOAT beta0, FLOAT x, FLOAT px, FLOAT y, FLOAT py, FLOAT delta, FLOAT tau, FLOAT pt, FLOAT chi,
    FLOAT s, INT Knlen, INT Kslen, FLOAT Kn[], FLOAT Ks[], FLOAT Hxl, FLOAT Hyl, FLOAT L, FLOAT Rel, FLOAT coordf[]){

    FLOAT betai, opd, dpx, dpy, hxx, hyy, a1l, b1l, zre, zim;
    INT nn;

    opd = 1 + delta;
    betai = ( 1/beta0 + pt) / opd;
    //multipole kick
    dpx=Kn[Knlen-1];
    dpy=Ks[Kslen-1];
    for(nn=Knlen-2;nn>=0;nn--){
        zre = ( dpx*x - dpy*y) / nn;
        zim = ( dpx*x + dpy*y) / nn;
        dpx = Kn[nn] + zre;
        dpy = Ks[nn] + zim;
    }
    dpx=-chi*dpx;
    dpy=chi*dpy;
    //curvature effect kick
    if(L!=0){
        b1l = chi * Kn[0]; 
        a1l = chi * Ks[0];
        hxx = Hxl / L*x;
        hyy = Hyl / L*y;
        dpx = dpx + Hxl + Hxl*delta - b1l*hxx;
        dpy = dpy + Hyl + Hyl*delta - a1l*hyy;
        tau = tau - chi * (hxx + hyy) * L * betai;
    }
    px = px + dpx;
    py = py + dpy;

    SETCOORDF(coordf,px,px);
    SETCOORDF(coordf,px,py);
}

INT multipole_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    INITPARTF;

    GETATTRI(multipole,Knlen);
    GETATTRI(multipole,Kslen);
//  GETATTRF(multipole,Knl);
//  GETATTRF(multipole,Ksl);
    GETATTRF(multipole,Hxl);
    GETATTRF(multipole,Hyl);
    GETATTRF(multipole,L);
    GETATTRF(multipole,Rel);

    GETCONSTF(partf,beta0);
    GETCOORDF(partf,x);
    GETCOORDF(partf,px);
    GETCOORDF(partf,y);
    GETCOORDF(partf,py);
    GETCOORDF(partf,delta);
    GETCOORDF(partf,tau);
    GETCOORDF(partf,pt);
    GETCOORDF(partf,chi);
    GETCOORDF(partf,s);
    for(;partid<partn;partid++){
      multipole_track(beta0, x, px, y, py, delta, tau, pt, chi, s, Knlen, Kslen, &elemf[elem_floatid],
                                    &elemf[elem_floatid+Knlen], Hxl, Hyl, L, Rel, GETPARTF(partid));
    };
    print_var(elemi,elemf,parti,partf,multipole_TYPE);
    return 1;
}