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

    x = abs(xx);
    y = abs(yy);

    // printf("%-6s %23.16e\n%-6s %23.16e\n","real", x, "imag", y);

    if(y < ylim && x < xlim )
    {
        q = ( 1.0 - y / ylim ) * sqrt( 1.0 - ( x / xlim )*( x / xlim ) );
        h = 1.0 / ( 3.2 * q );
        nc = 7 + (INT)( 23.0 * q );
        xl = exp( ( 1 - nc ) * log(h) );
        xh = y + 0.5 / h;
        yh = x;
        nu = 10 + (INT)( 21 * q );
        rx[nu] = 0.0;
        ry[nu] = 0.0;

        for( n = nu; n >= 1; n-- )
        {
            tx = xh + (FLOAT)(n) * rx[n];
            ty = yh - (FLOAT)(n) * ry[n];
            tn = tx*tx;
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
        wy = xx * sy;

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
            tn = tx*tx;
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
    FLOAT c,c1,c2,c3,c4,hf,p,sr0,sr,si,tr,ti,vi,vr,/*wi,wr,x,y,*/xa,xl,ya,zhi,zhr,z1,z10;
    FLOAT rr[37]={0},ri[37]={0};

    z1=1; hf=z1/2; z10=10;
    c1=74/z10; c2=83/z10; c3=z10/32; c4=16/z10;
    c=1.12837916709551257,p=46768052394588893.3825;


    xa = abs(x);
    ya = abs(y);

    if(ya < c1 && xa < c2){
        // zh = dcmplx(ya + c4, xa);
        zhr = ya + c4;
        zhi = xa;
        rr[37] = 0;
        ri[37] = 0;
        for( n = 36; n > 1; n--){
            // t = zh + n*dconjg(r(n+1));
            tr = zhr + n*rr[n+1];
            ti = zhi - n*ri[n+1];
            ti = zhi - (FLOAT)n * ri[n+1];
            // r[n] = hf * t / (dreal(t)*dreal(t) + dimag(t)*dimag(t));
            rr[n] = (hf * tr) / (tr*tr + ti*ti);
            ri[n] = (hf * ti) / (tr*tr + ti*ti);
        }
        xl = p;
        sr = 0;
        si = 0;
        for(n = 33; n > 1; n--){
            xl = c3 * xl;
            // s = r(n) * (s + xl)
            sr0 = rr[n] * (sr + xl) - ri[n] * si;
            si = rr[n] * si + ri[n] * (sr + xl);
            sr = sr0;
        }
        // v = c * s;
        vr = c * sr;
        vi = c * si;
    }
    else{
        zhr = ya;
        zhi = xa;
        rr[1] = 0;
        ri[1] = 0;
        for(n = 9; n > 1; n++){
            // t = zh + n * dconjg(r(1));
            tr = zhr + n * rr[1];
            tr = zhr + (FLOAT)n * rr[1];
            ti = zhi - n * ri[1];
            ti = zhi - (FLOAT)n * ri[1];
            // r(1) = hf * t / (dreal(t)*dreal(t) + dimag(t)*dimag(t));
            // rr[1] = hf * tr / (tr * tr + ti * ti);
            rr[1] = (hf * tr) / (tr * tr + ti * ti);
            // ri[1] = hf * ti / (tr * tr + ti * ti);
            ri[1] = (hf * ti) / (tr * tr + ti * ti);
        }
        // v = c * r[1];
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

// void wzset(){
    // INT idim,nx,ny;//kstep;
    // FLOAT h,*wtimag,*wtreal;//hrecip;//;//half,one,xcut,ycut;

    // // xcut = 7.77; ycut = 7.46;
    // h = 1.0/63.0;
    // nx = 490; ny = 470;
    // idim = (nx+2)*(ny+2);
    // // half = 0.5, one = 1.0;

    // wtreal = malloc(idim*sizeof(FLOAT));
    // wtimag = malloc(idim*sizeof(FLOAT));

    // // hrecip = 1 / h;
    // // kstep = nx + 2;
    // for( j = 0; j < ny + 1; j++){
    //     for( i = 0; i < nx + 1; i++){
    //         k = k + 1;
    //         x = (FLOAT)i * h;
    //         y = (FLOAT)j * h;
    //         mywwerf(x, y, wr, wi);
    //         wtreal[k] = wr;
    //         wtimag[k] = wi;
    //     }
    // }
// }

void wzsub(FLOAT x, FLOAT y, FLOAT *u, FLOAT *v){

    INT i,j,k,mu,nu;

    FLOAT a1,a2,b1,b2,d12i,d12r,d23i,d23r,d34i,d34r,p,q,qsq,r,simag,sreal,t,tdd13i,tdd13r,tdd24i,tdd24r,tdddi,tdddr,ti,
    tr,/*u,*/usum,usum3,/*v,*/vsum,vsum3,w1i,w1r,w2i,w2r,w3i,w3r,w4i,w4r,/*x,*/xh,xhrel,/*y,*/yh,yhrel;

    INT idim,nx,ny,kstep;
    FLOAT h,*wtimag,*wtreal,hrecip,xcut,ycut,half,one;
    FLOAT wi,wr;

    xcut = 7.77; ycut = 7.46;
    h = 1.0/63.0;
    nx = 490; ny = 470;
    idim = (nx+2)*(ny+2);
    half = 0.5, one = 1.0;

    a1 = 0.5124242248; a2 = 0.0517653588;
    b1 = 0.2752551286; b2 = 2.7247448714;

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

    // INT mbea, mcor, mcop, mmul, mpa, mran, nbb, nblo, nblz, ncom, ncor1, nelb, nele, nema, ninv, nlya, nmac, nmon1;
    // INT nper, nplo, npos, nran, nrco, ntr, nzfz;

    // nmac = 1;
    // nele=1200; nblo=600; nper=16; nelb=140; nblz=20000; nzfz = 300000; mmul = 20;
    // nran = 2000000; ncom = 100; mran = 500; mpa = 6; nrco = 5; nema = 15;
    // mcor = 10; mcop = mcor+6; mbea = 99;
    // npos = 20000; nlya = 10000; ninv = 1000; nplo = 20000;
    // nmon1 = 600; ncor1 = 600;
    // ntr = 20; nbb = 350;
    ss = 0;
    // INT i,j,k;
    FLOAT wi,wr,x,y;
    // INT mbea,mcor,mcop,mmul,mpa,mran,nbb,nblo,nblz,ncom,ncor1,nelb,nele,nema,ninv,nlya,nmac,nmon1;
    //nzfz,ntr,nrco,npart,nper,nplo,npos,nran;

    // /*npart = 64;*/ nmac = 1;
    // nele=1200; nblo=600; /*nper=16;*/ nelb=140; nblz=20000; /*nzfz = 300000;*/ mmul = 20;
    // /*nran = 2000000;*/ ncom = 100; mran = 500; mpa = 6; /*nrco = 5;*/ nema = 15;
    // mcor = 10; mcop = mcor+6; mbea = 99;
    // npos = 20000; nlya = 10000; ninv = 1000; /*nplo = 20000;*/
    // nmon1 = 600; ncor1 = 600;
    // /*ntr = 20;*/ nbb = 350;

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

    // INT idim, kstep, nx, ny;
    // FLOAT half, hrecip, one, xcut, ycut;//h,

    // xcut = 7.77; ycut = 7.46;
    // h = 1.0 / 63.0;
    // nx = 490; ny = 470;
    // idim = ( nx + 2 ) * ( ny + 2 );

    // FLOAT wtimag[idim], wtreal[idim];

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

void wofz(double *w1, double *w2, double x, double y)
  {
  short int b, quad;
  int /*k,*/ capn, nu;
  register int n, np1;
  double xy2, e, h;
  register double h2, lambda, c, r1, r2, s, s1, s2, t1, t2;

  if (y >= 0.0)
    if (x >= 0.0)
      quad = 1;
    else
    {
    quad = 2;
    x = fabs(x);
    }
  else
    if (x <= 0.0)
    {
    quad = 3;
    x = fabs(x);
    y = fabs(y);
    }         
    else
    {
    quad = 4;
    y = fabs(y);
    }
  if (y < 4.29 && x < 5.33)
      {
      s = (1.0 - y / 4.29) * sqrt(1.0 - x * x / 28.41);
      h = 1.6 * s;
      h2 = 2.0 * h;
      capn = ROUND(6.0 + 23.0 * s);
      nu = ROUND(9.0 + 21.0 * s);
      }   
  else
      {
      h = 0.0;
      capn = 0;
      nu = 8;
      }
  if (h > 0.0) lambda = pow(h2,(double)capn);
  b = h == 0.0 || lambda == 0.0;
  r1 = 0.0;
  r2 = 0.0;
  s1 = 0.0;
  s2 = 0.0;
  for (n = nu; n >= 0; n--)
      {
      np1 = n + 1;
      t1 = y + h + (double)np1 * r1;
      t2 = x - (double)np1 * r2;
      c = 0.5 / (t1 * t1 + t2 * t2);
      r1 = c * t1;
      r2 = c * t2;
      if (h > 0.0 && n <= capn)
      {
      t1 = lambda + s1;
      s1 = r1 * t1 - r2 * s2;
      s2 = r2 * t1 + r1 * s2;
      lambda /= h2;
      }
      }
  if (y == 0.0)
    *w1 = exp(-x*x);
  else
    if (b)
      *w1 = 1.12837916709551 * r1;
    else
      *w1 = 1.12837916709551 * s1;
  if (b)
    *w2 = 1.12837916709551 * r2;
  else
    *w2 = 1.12837916709551 * s2;
  if (quad == 3 || quad == 4)
      {
      e = 2.0 * exp(y*y-x*x);
      xy2 = 2.0 * x * y;
      c = cos(xy2) * e;
      s = sin(xy2) * e;
      *w1 = c - *w1;
      *w2 = s + *w2;
      }
  if (quad == 2 || quad == 3)
    *w2 *= -1.0;
  }


INT benchmark_errf(FLOAT input[]){
    
    FLOAT var_xx=input[0],var_yy=input[1],var_wx=1,var_wy=1,wx=input[2],wy=input[3];
    
    // printf("%-6s %23.16e\n%-6s %23.16e\n","real", input[0], "imag", input[1]);
    // printf("%-6s %23.16e\n%-6s %23.16e\n","real", var_xx, "imag", var_yy);
    
    // wofz(&var_wx, &var_wy, var_xx, var_yy);
    FLOAT var_napx = 1;
    wzsubv(&var_napx, &var_xx, &var_yy, &var_wx, &var_wy);
    
    // printf("%-6s %23.16e\n%-6s %23.16e\n",
    //     "real", var_wx, "imag", var_wy);
    printf("%-6s %23.16e %23.16e %23.16e\n%-6s %23.16e %23.16e %23.16e\n\n",
        "real", sqrt(pow((wx-var_wx),2)), var_wx, wx, "imag", sqrt(pow((wy-var_wy),2)), var_wy, wy);
    return 1;
}