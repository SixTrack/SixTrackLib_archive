#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

#define ROUND(x) (int)(x + 0.5)

FLOAT sign( FLOAT a, FLOAT b )
{
    if(b >= 0) return abs(a);
    else return -abs(a);
}

INT nint(FLOAT rval)
{
    INT temp_int = (INT)(rval*10 - (INT)(rval)*10);
    if(rval < 0.0){
        if( temp_int <= -5)
            return (rval - 0.5);
        else
            return (rval);
    }
    else{
        if( temp_int >= 5)
            return(rval + 0.5);
        else
            return (rval);
    }
}

void errf( FLOAT *var_xx, FLOAT *var_yy, FLOAT *var_wx, FLOAT *var_wy )
{
    INT n, nc, nu;
    FLOAT cc, h, q, rx[33], ry[33], saux, sx, sy, tn, tx, ty, wx, wy, x, xh, xl, xlim, xx, y, yh, ylim, yy;

    cc = 1.12837916709551;
    xlim = 5.33;
    ylim = 4.29;

    xx = *var_xx;
    yy = *var_yy;
    wx = *var_wx;
    wy = *var_wy;

    x = fabs(xx);
    y = fabs(yy);

    if(y < ylim && x < xlim )
    {
        q = ( 1.0 - y / ylim ) * sqrt( 1.0 - ( x / xlim )*( x / xlim ) );
        h = 1.0 / ( 3.2 * q );
        nc = 7 + (INT)( 23.0 * q );
        xl = pow(h,(1-nc));
        xh = y + 0.5 / h;
        yh = x;
        nu = 10 + (INT)( 21 * q );
        rx[nu] = 0.0;
        ry[nu] = 0.0;

        for( n = nu; n >= 1; n-- )
        {
            tx = xh + (FLOAT)(n) * rx[n];
            ty = yh - (FLOAT)(n) * ry[n];
            tn = tx*tx + ty*ty;
            rx[n-1] = ( 0.5 * tx ) / tn;
            ry[n-1] = ( 0.5 * ty ) / tn;
        }

        sx = 0.0;
        sy = 0.0;
        for( n = nc; n >= 1; n-- )
        {
            saux = sx + xl;
            sx = rx[n-1] * saux - ry[n-1] * sy;
            sy = rx[n-1] * sy + ry[n-1] * saux;
            xl = h * xl;
        }

        wx = cc * sx;
        wy = cc * sy;
    }
    else
    {
        xh = y;
        yh = x;
        rx[0] = 0.0;
        ry[0] = 0.0;
        for( n = 9; n >= 1; n-- )
        {
            tx = xh + (FLOAT)(n) * rx[0];
            ty = yh - (FLOAT)(n) * ry[0];
            tn = tx*tx + ty*ty;
            rx[0] = ( 0.5 * tx ) / tn;
            ry[0] = ( 0.5 * ty ) / tn;
        }

        wx = cc * rx[0];
        wy = cc * ry[0];

    }

    if( yy < 0.0 )
    {
        wx = ( 2.0 * exp( y*y - x*x ) ) * cos(( 2.0 * x ) * y ) - wx;
        wy = (( -1.0 * 2.0 ) * exp( y*y - x*x )) * sin(( 2.0 * x ) * y ) - wy;
        if( xx > 0.0 ) wy = -1.0 * wy;
    }
    else if( xx < 0.0 ) wy = -1.0 * wy;

    *var_xx = xx;
    *var_yy = yy;
    *var_wx = wx;
    *var_wy = wy;

}

void mywwerf(FLOAT x, FLOAT y, FLOAT *wr, FLOAT *wi){
    INT n;
    FLOAT c,c1,c2,c3,c4,hf,p,sr0,sr,si,tr,ti,vi,vr,xa,xl,ya,zhi,zhr,z1,z10;
    FLOAT rr[38]={0},ri[38]={0};

    z1=1; hf=z1/2; z10=10;
    c1=74/z10; c2=83/z10; c3=z10/32; c4=16/z10;
    c=1.12837916709551257,p=46768052394588893.3825;


    xa = fabs(x);
    ya = fabs(y);

    if(ya < c1 && xa < c2){
        zhr = ya + c4;
        zhi = xa;
        rr[37] = 0;
        ri[37] = 0;
        for( n = 36; n >= 1; n--){
            tr = zhr + (FLOAT)n * rr[n+1];
            ti = zhi - (FLOAT)n * ri[n+1];
            rr[n] = (hf * tr) / (tr*tr + ti*ti);
            ri[n] = (hf * ti) / (tr*tr + ti*ti);
        }
        xl = p;
        sr = 0;
        si = 0;
        for(n = 33; n >= 1; n--){
            xl = c3 * xl;
            sr0 = rr[n] * (sr + xl) - ri[n] * si;
            si = rr[n] * si + ri[n] * (sr + xl);
            sr = sr0;
        }
        vr = c * sr;
        vi = c * si;
    }
    else{
        zhr = ya;
        zhi = xa;
        rr[1] = 0;
        ri[1] = 0;
        for(n = 9; n >= 1; n--){
            tr = zhr + n * rr[1];
            tr = zhr + (FLOAT)n * rr[1];
            ti = zhi - n * ri[1];
            ti = zhi - (FLOAT)n * ri[1];
            rr[1] = (hf * tr) / (tr * tr + ti * ti);
            ri[1] = (hf * ti) / (tr * tr + ti * ti);
        }
        vr = c * rr[1];
        vi = c * ri[1];
    }
    if(ya == 0){
        vr = exp(-1*xa*xa);
    }
    if(ya < 0){
        vr = (2 * exp( ya*ya - xa*xa)) * cos( ( 2*xa ) * ya) - vr;
        vi = (-2 * exp( ya*ya - xa*xa)) * sin( ( 2*xa ) * ya) - vi;
        if( x > 0) 
            vi = -1 * vi;
    }
    else{
        if ( x < 0)
            vi = -1* vi;
    }
    *wr = vr;
    *wi = vi;
}



void wzsub(FLOAT x, FLOAT y, FLOAT *u, FLOAT *v){

    INT i,j,k,mu,nu;

    FLOAT a1,a2,b1,b2,d12i,d12r,d23i,d23r,d34i,d34r,p,q,qsq,r,simag,sreal,t,tdd13i,tdd13r,tdd24i,tdd24r,tdddi,tdddr,ti,
    tr,usum,usum3,vsum,vsum3,w1i,w1r,w2i,w2r,w3i,w3r,w4i,w4r,xh,xhrel,yh,yhrel;

    INT nx,ny,kstep;
    FLOAT h,hrecip,xcut,ycut,half,one;
    FLOAT wi=0,wr=0,x1,y1;

    xcut = 7.77; ycut = 7.46;
    h = 1.0/63.0;
    nx = 490; ny = 470;
    half = 0.5, one = 1.0;

    a1 = 0.5124242248; a2 = 0.0517653588;
    b1 = 0.2752551286; b2 = 2.7247448714;

    FLOAT wtimag[232224]={0},wtreal[232224]={0};

    hrecip = 1 / h;
    kstep = nx + 2;
    k = 0;
    for( j = 0; j < ny+2; j++){
        for( i = 0; i < nx+2; i++){
            k = k + 1;
            x1 = (FLOAT)i * h;
            y1 = (FLOAT)j * h;
            mywwerf(x1, y1, &wr, &wi);
            wtreal[k] = wr;
            wtimag[k] = wi;
        }
    }
    if ( x > xcut || y > ycut){
        p = x*x - y*y;
        q = 2 * x * y;
        qsq = q * q;
        //First Term
        t = p - b1;
        r = a1 / (t*t + qsq);
        sreal = r*t;
        simag = (-1 * r) * q;
        //Second Term
        t = p - b2;
        r = a2 / (t*t + qsq);
        sreal = sreal + r * t;
        simag = simag - r * q;
        //Multiply by i*z
        *u = -1 * (y * sreal + x * simag);
        *v = (x * sreal - y * simag);
    }
    else{
        xh = hrecip * x;
        yh = hrecip * y;
        mu = (INT)xh;
        nu = (INT)yh;
        //Compute divided differences
        k = 2 + mu + nu * kstep;
        w4r = wtreal[k];
        w4i = wtimag[k];
        k = k - 1;
        w3r = wtreal[k];
        w3i = wtimag[k];
        d34r = w4r - w3r;
        d34i = w4i - w3i;
        k = k + kstep;
        w2r = wtreal[k];
        w2i = wtimag[k];
        d23r = w2i - w3i;
        d23i = w3r - w2r;
        tr = d23r - d34r;
        ti = d23i - d34i;
        tdd24r = ti - tr;
        tdd24i = -1 * (tr + ti);
        k = k + 1;
        w1r = wtreal[k];
        w1i = wtimag[k];
        d12r = w1r - w2r;
        d12i = w1i - w2i;
        tr = d12r - d23r;
        ti = d12i - d23i;
        tdd13r = tr + ti;
        tdd13i = ti - tr;
        tdddr = tdd13i - tdd24i;
        tdddi = tdd24r - tdd13r;
        //Evaluate Polynomial
        xhrel = xh - (FLOAT)mu;
        yhrel = yh - (FLOAT)nu;
        usum3 = half*( tdd13r + ( xhrel*tdddr - yhrel*tdddi ) );
        vsum3 = half*( tdd13i + ( xhrel*tdddi + yhrel*tdddr ) );
        yhrel = yhrel - one;
        usum = d12r + ( xhrel*usum3 - yhrel*vsum3 );
        vsum = d12i + ( xhrel*vsum3 + yhrel*usum3 );
        xhrel = xhrel - one;
        *u = w1r + ( xhrel*usum - yhrel*vsum );
        *v = w1i + ( xhrel*vsum + yhrel*usum );
    }
}

void wzsubv( INT *var_napx, FLOAT *vx, FLOAT *vy, FLOAT *vu, FLOAT *vv ){

    const INT npart = 64;

    INT i, j, k, napx, vmu[npart], vnu[npart];
    FLOAT a1, a2, b1, b2, ss, vd12i[npart], vd12r[npart], vd23i[npart], vd23r[npart], vd34i[npart], vd34r[npart], vp[npart];
    FLOAT vq[npart], vqsq[npart], vr[npart], vsimag[npart], vsreal[npart], vt[npart], vtdd13i[npart], vtdd13r[npart];
    FLOAT vtdd24i[npart], vtdd24r[npart], vtdddi[npart], vtdddr[npart], vti[npart], vtr[npart];
    FLOAT vusum[npart], vusum3[npart], vvsum[npart], vvsum3[npart], vw1i[npart], vw1r[npart], vw2i[npart];
    FLOAT vw2r[npart], vw3i[npart], vw3r[npart], vw4i[npart], vw4r[npart], vxh[npart], vxhrel[npart];
    FLOAT vyh[npart], vyhrel[npart];

    ss = 0;

    FLOAT wi,wr,x,y;
    INT idim,nx,ny,kstep;
    FLOAT h,*wtimag,*wtreal,hrecip,xcut,ycut,half,one;

    xcut = 7.77; ycut = 7.46;
    h = 1.0/63.0;
    nx = 490; ny = 470;
    idim = (nx+2)*(ny+2);
    half = 0.5, one = 1.0;

    wtreal = malloc(idim*sizeof(FLOAT));
    wtimag = malloc(idim*sizeof(FLOAT));

    hrecip = 1 / h;
    kstep = nx + 2;
    k = 0;
    for( j = 0; j < ny + 1; j++){
        for( i = 0; i < nx + 1; i++){
            k = k + 1;
            x = (FLOAT)i * h;
            y = (FLOAT)j * h;
            mywwerf(x, y, &wr, &wi);
            wtreal[k] = wr;
            wtimag[k] = wi;
        }
    }

    a1 = 0.5124242248; a2 = 0.0517653588;
    b1 = 0.2752551286; b2 = 2.7247448714;

    napx = *var_napx;

    for( j=1; j <= napx; j++ ){
        if( vx[j] >= xcut || vy[j] >= ycut ){
            ss = ss + sign( 1.0, sign( 1.0, vx[j] - xcut ) + sign( 1.0, vy[j] - ycut ) );
        }
    }

    if ( nint(ss) == napx ){
        for( j=1; j <= napx; j++){
            
            vp[j] = vx[j] * vx[j] - vy[j] * vy[j];
            vq[j] = ( 2.0 * vx[j] ) * vy[j];
            vqsq[j] = vq[j] * vq[j];
            
            //  First term.
            vt[j] = vp[j] - b1;
            vr[j] = a1 / ( vt[j] * vt[j] + vqsq[j] );
            vsreal[j] = vr[j] * vt[j];
            vsimag[j] = ( -1 * vr[j]) * vq[j];
            
            //  Second term
            vt[j] = vp[j] - b2;
            vr[j] = a2 / ( vt[j] * vt[j] + vqsq[j] );
            vsreal[j] = vsreal[j] + vr[j] * vt[j];
            vsimag[j] = vsimag[j] - vr[j] * vq[j];
            
            //  Multiply by i*z.
            vu[j] = -1 * ( vy[j] * vsreal[j] + vx[j] * vsimag[j] );
            vv[j] = vx[j] * vsreal[j] - vy[j] * vsimag[j];
        }
    }
    else if ( nint(ss) != -napx){
        
        for( j=1; j <= napx; j++){
            
            if( vx[j] >= xcut || vy[j] >= ycut ){

                vp[j] = vx[j] * vx[j] - vy[j] * vy[j];
                vq[j] = ( 2.0 * vx[j] ) * vy[j];
                vqsq[j] = vq[j] * vq[j];
                
                //  First term.
                vt[j] = vp[j] - b1;
                vr[j] = a1 / (vt[j] * vt[j] + vqsq[j] );
                vsreal[j] = vr[j] * vt[j];
                vsimag[j] = ( -1 * vr[j] ) * vq[j];
                
                //  Second term
                vt[j] = vp[j] - b2;
                vr[j] = a2 / (vt[j] * vt[j] + vqsq[j] );
                vsreal[j] = vsreal[j] + vr[j] * vt[j];
                vsimag[j] = vsimag[j] - vr[j] * vq[j];
                
                //  Multiply by i*z.
                vu[j] = -1 * ( vy[j] * vsreal[j] + vx[j] * vsimag[j] );
                vv[j] = vx[j] * vsreal[j] - vy[j] * vsimag[j];
            }

            else{

                vxh[j] = hrecip * vx[j];
                vyh[j] = hrecip * vy[j];
                vmu[j] = ( INT ) vxh[j];
                vnu[j] = ( INT ) vyh[j];

                //  Compute divided differences.
                k = 2 + vmu[j] + vnu[j] * kstep;
                vw4r[j] = wtreal[k];
                vw4i[j] = wtimag[k];
                k = k - 1;
                vw3r[j] = wtreal[k];
                vw3i[j] = wtimag[k];
                vd34r[j] = vw4r[j] - vw3r[j];
                vd34i[j] = vw4i[j] - vw3i[j];
                k = k + kstep;
                vw2r[j] = wtreal[k];
                vw2i[j] = wtimag[k];
                vd23r[j] = vw2i[j] - vw3i[j];
                vd23i[j] = vw3r[j] - vw2r[j];
                vtr[j] = vd23r[j] - vd34r[j];
                vti[j] = vd23i[j] - vd34i[j];
                vtdd24r[j] = vti[j] - vtr[j];
                vtdd24i[j] = -1 * ( vtr[j] + vti[j] );
                k = k + 1;
                vw1r[j] = wtreal[k];
                vw1i[j] = wtimag[k];
                vd12r[j] = vw1r[j] - vw2r[j];
                vd12i[j] = vw1i[j] - vw2i[j];
                vtr[j] = vd12r[j] - vd23r[j];
                vti[j] = vd12i[j] - vd23i[j];
                vtdd13r[j] = vtr[j] + vti[j];
                vtdd13i[j] = vti[j] - vtr[j];
                vtdddr[j] = vtdd13i[j] - vtdd24i[j];
                vtdddi[j] = vtdd24r[j] - vtdd13r[j];
                
                //  Evaluate polynomial.
                vxhrel[j] = vxh[j] - ( FLOAT ) vmu[j];
                vyhrel[j] = vyh[j] - ( FLOAT ) vnu[j];
                vusum3[j] = half * ( vtdd13r[j] + ( vxhrel[j] * vtdddr[j] - vyhrel[j] * vtdddi[j] ) );
                vvsum3[j] = half * ( vtdd13i[j] + ( vxhrel[j] * vtdddi[j] + vyhrel[j] * vtdddr[j] ) );
                vyhrel[j] = vyhrel[j] - one;
                vusum[j] = vd12r[j] + ( vxhrel[j] * vusum3[j] - vyhrel[j] * vvsum3[j] );
                vvsum[j] = vd12i[j] + ( vxhrel[j] * vvsum3[j] + vyhrel[j] * vusum3[j] );
                vxhrel[j] = vxhrel[j] - one;
                vu[j] = vw1r[j] + ( vxhrel[j] * vusum[j] - vyhrel[j] * vvsum[j] );
                vv[j] = vw1i[j] + ( vxhrel[j] * vvsum[j] + vyhrel[j] * vusum[j] );
            }
        }  
    }
    else{
        for( j=1; j <= napx; j++){
            vxh[j] = hrecip * vx[j];
            vyh[j] = hrecip * vy[j];
            vmu[j] = ( INT ) vxh[j];
            vnu[j] = ( INT ) vyh[j];
            
            //  Compute divided differences.
            k = 2 + vmu[j] + vnu[j] * kstep;
            vw4r[j] = wtreal[k];
            vw4i[j] = wtimag[k];
            k = k - 1;
            vw3r[j] = wtreal[k];
            vw3i[j] = wtimag[k];
            vd34r[j] = vw4r[j] - vw3r[j];
            vd34i[j] = vw4i[j] - vw3i[j];
            k = k + kstep;
            vw2r[j] = wtreal[k];
            vw2i[j] = wtimag[k];
            vd23r[j] = vw2i[j] - vw3i[j];
            vd23i[j] = vw3r[j] - vw2r[j];
            vtr[j] = vd23r[j] - vd34r[j];
            vti[j] = vd23i[j] - vd34i[j];
            vtdd24r[j] = vti[j] - vtr[j];
            vtdd24i[j] = -1 * ( vtr[j] + vti[j] );
            k = k + 1;
            vw1r[j] = wtreal[k];
            vw1i[j] = wtimag[k];
            vd12r[j] = vw1r[j] - vw2r[j];
            vd12i[j] = vw1i[j] - vw2i[j];
            vtr[j] = vd12r[j] - vd23r[j];
            vti[j] = vd12i[j] - vd23i[j];
            vtdd13r[j] = vtr[j] + vti[j];
            vtdd13i[j] = vti[j] - vtr[j];
            vtdddr[j] = vtdd13i[j] - vtdd24i[j];
            vtdddi[j] = vtdd24r[j] - vtdd13r[j];
            
            //  Evaluate polynomial.
            vxhrel[j] = vxh[j] - ( FLOAT ) vmu[j];
            vyhrel[j] = vyh[j] - ( FLOAT ) vnu[j];
            vusum3[j] = half * ( vtdd13r[j] + ( vxhrel[j] * vtdddr[j] - vyhrel[j] * vtdddi[j] ) );
            vvsum3[j] = half * ( vtdd13i[j] + ( vxhrel[j] * vtdddi[j] + vyhrel[j] * vtdddr[j] ) );
            vyhrel[j] = vyhrel[j] - one;
            vusum[j] = vd12r[j] + ( vxhrel[j] * vusum3[j] - vyhrel[j] * vvsum3[j] );
            vvsum[j] = vd12i[j] + ( vxhrel[j] * vvsum3[j] + vyhrel[j] * vusum3[j] );
            vxhrel[j] = vxhrel[j] - one;
            vu[j] = vw1r[j] + ( vxhrel[j] * vusum[j] - vyhrel[j] * vvsum[j] );
            vv[j] = vw1i[j] + ( vxhrel[j] * vvsum[j] + vyhrel[j] * vusum[j] );
        }
    }
}

INT benchmark_errf(FLOAT input[]){
    
    FLOAT var_xx=input[0],var_yy=input[1],var_wx=1,var_wy=1,wx=input[2],wy=input[3];

    /*UNCOMMENT TO BENCHMARK WITH wzsub()*/
    // INT var_napx = 1;
    // wzsubv(&var_napx, &var_xx, &var_yy, &var_wx, &var_wy);

    /*UNCOMMENT TO BENCHMARK WITH wzsub()*/
    wzsub(var_xx, var_yy, &var_wx, &var_wy);

    /*UNCOMMENT TO BENCHMARK WITH errf()*/
    // errf(&var_xx, &var_yy, &var_wx, &var_wy);
    
    printf("%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n\n",
        "real", sqrt(pow((wx-var_wx),2)), var_wx, wx, "imag", sqrt(pow((wy-var_wy),2)), var_wy, wy);
    return 1;
}