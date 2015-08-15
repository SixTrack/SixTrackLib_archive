#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define align_TYPE                                              9
#define align_float_dx                                          0
#define align_float_dy                                          1
#define align_float_tilt                                        2

void print_var(INT [], FLOAT [], INT [], FLOAT [], INT );

inline void align_track(FLOAT x, FLOAT px, FLOAT y, FLOAT py, FLOAT dx, FLOAT dy, FLOAT tilt, FLOAT coordf[]){
    
    FLOAT an, cx, sx, xn, yn, pxn, pyn;

    an = -1 * tilt * M_PI / 180;
    cx = cos(an);
    sx = sin(an);
    // printf("c cx: %23.16e\nc sx: %23.16e\n", cx, sx);
    xn = -1 * dx;
    yn = -1 * dy;
    // printf("c xn: %23.16e\nc yn: %23.16e\n", xn, yn);
    xn = xn + cx * x + sx * y;
    yn = yn - sx * x + cx * y;
    // printf("c xn: %23.16e\nc yn: %23.16e\n", xn, yn);
    x = xn;
    y = yn;
    // printf("c px: %23.16e\nc py: %23.16e\n", px, py);
    pxn = cx * px + sx * py;
    // printf("c cx * px: %23.16e\nc sx * py: %23.16e\n", cx * px, sx * py);
    pyn = cx * py - sx * px;
    // printf("c pxn: %23.16e\nc pyn: %23.16e\n", pxn, pyn);
    px = pxn;
    py = pyn;
    
    SETCOORDF(coordf,x,x);
    SETCOORDF(coordf,y,y);
    SETCOORDF(coordf,px,px);
    SETCOORDF(coordf,py,py);
}

INT align_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    INITPARTF;

    GETATTRF(align,dx);
    GETATTRF(align,dy);
    GETATTRF(align,tilt);

    GETCOORDF(partf,x);
    GETCOORDF(partf,px);
    GETCOORDF(partf,y);
    GETCOORDF(partf,py);
    for(;partid<partn;partid++){
      align_track(x, px, y, py, dx, dy, tilt, GETPARTF(partid));
    };
    print_var(elemi,elemf,parti,partf,align_TYPE);
    return 1;
}