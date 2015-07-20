#include "hmacro.h"
#include "extra.c"
#include <math.h>
#include <stdio.h>

#define beambeam_TYPE                                           30
#define beambeam_float_HorBeamBeamSeparation                    0
#define beambeam_float_VerBeamBeamSeparation                    1
#define beambeam_float_L                                        2
#define beambeam_float_ClosedOrbitBeamX                         3
#define beambeam_float_ClosedOrbitBeamY                         4
#define beambeam_float_ClosedOrbitBeamSigma                     5
#define beambeam_float_ClosedOrbitBeamPx                        6
#define beambeam_float_ClosedOrbitBeamPy                        7
#define beambeam_float_ClosedOrbitBeamDelta                     8
#define beambeam_float_BeamOffsetX                              9
#define beambeam_float_BeamOffsetY                              10
#define beambeam_float_BeamOffsetSigma                          11
#define beambeam_float_BeamOffsetPx                             12
#define beambeam_float_BeamOffsetPy                             13
#define beambeam_float_BeamOffsetDelta                          14
#define beambeam_float_bbcu11                                   15
#define beambeam_float_bbcu12                                   16
#define beambeam_float_SigmaNqX                                 17
#define beambeam_float_SigmaNqY                                 18
#define beambeam_float_SquareOfSigmaNX                          19
#define beambeam_float_SquareOfSigmaNY                          20
#define beambeam_int_SwitchToLinearCoupling                     0
#define beambeam_int_NoOfParticles                              1
#define beambeam_int_SwitchToFastBeamBeamAlgo                   2
#define beambeam_int_BeambeamType                               3

INT beambeam_type1_calc(INT pfstart, FLOAT x, FLOAT y, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT HorBeamBeamSeparation, FLOAT VerBeamBeamSeparation, FLOAT L, FLOAT ClosedOrbitBeamX, FLOAT ClosedOrbitBeamY, FLOAT ClosedOrbitBeamSigma, FLOAT ClosedOrbitBeamPx, FLOAT ClosedOrbitBeamPy, FLOAT ClosedOrbitBeamDelta, FLOAT BeamOffsetX, FLOAT BeamOffsetY, FLOAT BeamOffsetSigma, FLOAT BeamOffsetPx, FLOAT BeamOffsetPy, FLOAT BeamOffsetDelta, FLOAT bbcu11, FLOAT bbcu12, FLOAT SigmaNqX, FLOAT SigmaNqY, FLOAT SquareOfSigmaNX, FLOAT SquareOfSigmaNY, INT SwitchToLinearCoupling, FLOAT partf[]){
    FLOAT crkvebj,cikvebj,rho2bj,tkbj,cccc;
    INT cntbb1 = 0;

    if( SwitchToLinearCoupling == 0 )
    {
        crkvebj = ( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation;
        cikvebj = ( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation;
    }
    else
    {
        crkvebj = (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu11 + (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu12;
        cikvebj = (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu11 - (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu12;
    }

    rho2bj = crkvebj*crkvebj + cikvebj*cikvebj;
    if( rho2bj <= OnePoweredToMinus38 ) return 1;

    tkbj = rho2bj / ( 2.0 * SquareOfSigmaNX );

    if( SwitchToLinearCoupling == 0 )
    {
        px = px + RatioPtoPj * ((( L * crkvebj ) / rho2bj ) * ( 1.0 - exp( -1.0 * tkbj )) - BeamOffsetPx );
        py = py + RatioPtoPj * ((( L * cikvebj ) / rho2bj ) * ( 1.0 - exp( -1.0 * tkbj )) - BeamOffsetPy );
    }
    else
    {
        cccc = ((( L * crkvebj ) / rho2bj ) * ( 1.0 - exp( -1.0 * tkbj )) - BeamOffsetPx ) * bbcu11 - ((( L * cikvebj ) / rho2bj ) * ( 1.0 - exp( -1.0 * tkbj )) - BeamOffsetPy ) * bbcu12;

        px = px + RatioPtoPj * cccc;
        cccc = ((( L * crkvebj ) / rho2bj ) * ( 1.0 - exp( -1.0 * tkbj )) - BeamOffsetPx ) * bbcu12 + ((( L * cikvebj ) / rho2bj ) * ( 1.0 - exp( -1.0 * tkbj )) - BeamOffsetPy ) * bbcu11;

        py = py + RatioPtoPj * cccc;
    }

    SETCOORDF(partf,px,px);
    SETCOORDF(partf,py,py);
    
    if( cntbb1++ == 0 ) printf("beam beam 1\n");
    return 1;
}

INT beambeam_type2_calc(INT pfstart, FLOAT x, FLOAT y, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT HorBeamBeamSeparation, FLOAT VerBeamBeamSeparation, FLOAT L, FLOAT ClosedOrbitBeamX, FLOAT ClosedOrbitBeamY, FLOAT ClosedOrbitBeamSigma, FLOAT ClosedOrbitBeamPx, FLOAT ClosedOrbitBeamPy, FLOAT ClosedOrbitBeamDelta, FLOAT BeamOffsetX, FLOAT BeamOffsetY, FLOAT BeamOffsetSigma, FLOAT BeamOffsetPx, FLOAT BeamOffsetPy, FLOAT BeamOffsetDelta, FLOAT bbcu11, FLOAT bbcu12, FLOAT SigmaNqX, FLOAT SigmaNqY, FLOAT SquareOfSigmaNX, FLOAT SquareOfSigmaNY, INT SwitchToLinearCoupling, INT NoOfParticles, INT SwitchToFastBeamBeamAlgo, FLOAT crxbj, FLOAT crzbj, FLOAT cbxbj, FLOAT cbzbj, FLOAT partf[]){
    FLOAT crkvebj,cikvebj,rho2bj,tkbj,cccc,r2bj,rbj,rkbj,xbbj,zbbj,xrbj,zrbj;
    FLOAT SquareRootOfPi=sqrt(Pi);
    INT cntbb2_0=0,cntbb21 =0;

    if( SwitchToFastBeamBeamAlgo == 0 )
    {
        r2bj = 2.0 * ( SquareOfSigmaNX - SquareOfSigmaNY );
        rbj = sqrt(r2bj);

        rkbj = ( L * SquareRootOfPi ) / rbj;

        if( SwitchToLinearCoupling == 0 )
        {
            crkvebj = ( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation;
            cikvebj = ( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation;
        }
        else
        {
            crkvebj = (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu11 + (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu12;
            cikvebj = (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu11 - (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu12;
        }

        xrbj = abs(crkvebj) / rbj;
        zrbj = abs(cikvebj) / rbj;

        errf( &xrbj, &zrbj, &crxbj, &crzbj );

        tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

        xbbj = SigmaNqY * xrbj;
        zbbj = SigmaNqX * zrbj;

        errf( &xbbj, &zbbj, &cbxbj, &cbzbj );

        if( SwitchToLinearCoupling == 0 )
        {
            px = px + RatioPtoPj * (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) *sign( 1.0, crkvebj ) - BeamOffsetPx );
            py = py + RatioPtoPj * (( rkbj * ( crxbj - exp( -1.0 * tkbj ) * cbxbj )) *sign( 1.0, cikvebj ) - BeamOffsetPy );
        }
        else
        {
            cccc = (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu11 - (( rkbj * ( crxbj - exp(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu12;
            px = px + RatioPtoPj * cccc;

            cccc = (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu12 + (( rkbj * ( crxbj - exp(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu11;
            py = py + RatioPtoPj * cccc;
        }

        if( cntbb2_0++ == 0 ) printf("beam beam 2 type 0\n");

    }
    else if(  SwitchToFastBeamBeamAlgo == 1 )
    {
        r2bj = 2.0 * ( SquareOfSigmaNX - SquareOfSigmaNY );
        rbj = sqrt(r2bj);

        rkbj = ( L * SquareRootOfPi ) / rbj;

        if( SwitchToLinearCoupling == 0 )
        {
            crkvebj = ( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation;
            cikvebj = ( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation;
        }
        else
        {
            crkvebj = (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu11 + (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu12;
            cikvebj = (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu11 - (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu12;
        }

        xrbj = abs(crkvebj) / rbj;
        zrbj = abs(cikvebj) / rbj;

        tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

        xbbj = SigmaNqY * xrbj;
        zbbj = SigmaNqX * zrbj;

        if( ( cntbb21++ ) % 60 == 0 )
        {
            wzsubv( &NoOfParticles, &xrbj, &zrbj, &crxbj, &crzbj );
            wzsubv( &NoOfParticles, &xbbj, &zbbj, &cbxbj, &cbzbj );
        }

        tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

        if( SwitchToLinearCoupling == 0 )
        {
            px = px + RatioPtoPj * (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) *sign( 1.0, crkvebj ) - BeamOffsetPx );
            py = py + RatioPtoPj * (( rkbj * ( crxbj - exp( -1.0 * tkbj ) * cbxbj )) *sign( 1.0, cikvebj ) - BeamOffsetPy );
        }
        else
        {
            cccc = (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu11 - (( rkbj * ( crxbj - exp(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu12;
            px = px + RatioPtoPj * cccc;

            cccc = (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu12 + (( rkbj * ( crxbj - exp(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu11;
            py = py + RatioPtoPj * cccc;
        }
    }

    SETCOORDF(partf,px,px);
    SETCOORDF(partf,py,py);
}

INT beambeam_type3_calc(INT pfstart, FLOAT x, FLOAT y, FLOAT px, FLOAT py, FLOAT RatioPtoPj, FLOAT HorBeamBeamSeparation, FLOAT VerBeamBeamSeparation, FLOAT L, FLOAT ClosedOrbitBeamX, FLOAT ClosedOrbitBeamY, FLOAT ClosedOrbitBeamSigma, FLOAT ClosedOrbitBeamPx, FLOAT ClosedOrbitBeamPy, FLOAT ClosedOrbitBeamDelta, FLOAT BeamOffsetX, FLOAT BeamOffsetY, FLOAT BeamOffsetSigma, FLOAT BeamOffsetPx, FLOAT BeamOffsetPy, FLOAT BeamOffsetDelta, FLOAT bbcu11, FLOAT bbcu12, FLOAT SigmaNqX, FLOAT SigmaNqY, FLOAT SquareOfSigmaNX, FLOAT SquareOfSigmaNY, INT SwitchToLinearCoupling, INT NoOfParticles, INT SwitchToFastBeamBeamAlgo, FLOAT crxbj, FLOAT crzbj, FLOAT cbxbj, FLOAT cbzbj, FLOAT partf[]){
    FLOAT crkvebj, cikvebj, rho2bj, tkbj, cccc, r2bj, rbj, rkbj, xbbj, zbbj, xrbj, zrbj;
    FLOAT SquareRootOfPi = sqrt(Pi);
    INT cntbb3_0=0,cntbb31=0;

    if( SwitchToFastBeamBeamAlgo == 0 )
    {
        r2bj = 2.0 * ( SquareOfSigmaNY - SquareOfSigmaNX );
        rbj = sqrt(r2bj);

        rkbj = ( L * SquareRootOfPi ) / rbj;

        if( SwitchToLinearCoupling == 0 )
        {
            crkvebj = ( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation;
            cikvebj = ( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation;
        }
        else
        {
            crkvebj = (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu11 + (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu12;
            cikvebj = (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu11 + (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu12;
        }

        xrbj = abs(crkvebj) / rbj;
        zrbj = abs(cikvebj) / rbj;

        errf( &zrbj, &xrbj, &crzbj, &crxbj );

        tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

        xbbj = SigmaNqY * xrbj;
        zbbj = SigmaNqX * zrbj;

        errf( &zbbj, &xbbj, &cbzbj, &cbxbj );

        if( SwitchToLinearCoupling == 0 )
        {
            px = px + RatioPtoPj * (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) *sign( 1.0, crkvebj ) - BeamOffsetPx );
            py = py + RatioPtoPj * (( rkbj * ( crxbj - exp( -1.0 * tkbj ) * cbxbj )) *sign( 1.0, cikvebj ) - BeamOffsetPy );
        }
        else
        {
            cccc = (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu11 - (( rkbj * ( crxbj - exp(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu12;
            px = px + RatioPtoPj * cccc;

            cccc = (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu12 + (( rkbj * ( crxbj - exp(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu11;
            py = py + RatioPtoPj * cccc;
        }

        if( cntbb3_0++ == 0 ) printf(" Beam Beam type 3 0 \n");

    }
    else if(  SwitchToFastBeamBeamAlgo == 1 )
    {
        r2bj = 2.0 * ( SquareOfSigmaNY - SquareOfSigmaNX );
        rbj = sqrt(r2bj);

        rkbj = ( L * SquareRootOfPi ) / rbj;

        if( SwitchToLinearCoupling == 0 )
        {
            crkvebj = ( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation;
            cikvebj = ( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation;
        }
        else
        {
            crkvebj = (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu11 + (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu12;
            cikvebj = (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu11 - (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu12;
        }

        xrbj = abs(crkvebj) / rbj;
        zrbj = abs(cikvebj) / rbj;

        tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

        xbbj = SigmaNqY * xrbj;
        zbbj = SigmaNqX * zrbj;

        if( ( cntbb31++ ) % 60 == 0 )
        {
            wzsubv( &NoOfParticles, &zrbj, &xrbj, &crzbj, &crxbj );
            wzsubv( &NoOfParticles, &zbbj, &xbbj, &cbzbj, &cbxbj );
        }

        tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

        if( SwitchToLinearCoupling == 0 )
        {
            px = px + RatioPtoPj * (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) *sign( 1.0, crkvebj ) - BeamOffsetPx );
            py = py + RatioPtoPj * (( rkbj * ( crxbj - exp( -1.0 * tkbj ) * cbxbj )) *sign( 1.0, cikvebj ) - BeamOffsetPy );
        }
        else
        {
            cccc = (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu11 - (( rkbj * ( crxbj - exp(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu12;
            px = px + RatioPtoPj * cccc;

            cccc = (( rkbj * ( crzbj - exp( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu12 + (( rkbj * ( crxbj - exp(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu11;
            py = py + RatioPtoPj * cccc;
        }
    }

    SETCOORDF(partf,px,px);
    SETCOORDF(partf,py,py);
}

INT beambeam_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT ret=0;
    INT RatioPtoPj;
    ELEMINIT;
    INITPARTF;
    GETCOORDF(partf,x);
    GETCOORDF(partf,y);
    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,ps);
    GETCOORDF(partf,crxbj);
    GETCOORDF(partf,crzbj);
    GETCOORDF(partf,cbxbj);
    GETCOORDF(partf,cbzbj);

    GETATTRF(beambeam,HorBeamBeamSeparation);
    GETATTRF(beambeam,VerBeamBeamSeparation);
    GETATTRF(beambeam,L);
    GETATTRF(beambeam,ClosedOrbitBeamX);
    GETATTRF(beambeam,ClosedOrbitBeamY);
    GETATTRF(beambeam,ClosedOrbitBeamSigma);
    GETATTRF(beambeam,ClosedOrbitBeamPx);
    GETATTRF(beambeam,ClosedOrbitBeamPy);
    GETATTRF(beambeam,ClosedOrbitBeamDelta);
    GETATTRF(beambeam,BeamOffsetX);
    GETATTRF(beambeam,BeamOffsetY);
    GETATTRF(beambeam,BeamOffsetSigma);
    GETATTRF(beambeam,BeamOffsetPx);
    GETATTRF(beambeam,BeamOffsetPy);
    GETATTRF(beambeam,BeamOffsetDelta);
    GETATTRF(beambeam,bbcu11);
    GETATTRF(beambeam,bbcu12);
    GETATTRF(beambeam,SigmaNqX);
    GETATTRF(beambeam,SigmaNqY);
    GETATTRF(beambeam,SquareOfSigmaNX);
    GETATTRF(beambeam,SquareOfSigmaNY);
    GETATTRI(beambeam,SwitchToLinearCoupling);
    GETATTRI(beambeam,NoOfParticles);
    GETATTRI(beambeam,SwitchToFastBeamBeamAlgo);
    GETATTRI(beambeam,BeambeamType);
    
    RatioPtoPj = One / ( One + ps );
    switch(BeambeamType){
        case 1: ret = beambeam_type1_calc(pfstart, x, y, px, py, RatioPtoPj, HorBeamBeamSeparation,VerBeamBeamSeparation,L,ClosedOrbitBeamX,ClosedOrbitBeamY,ClosedOrbitBeamSigma,ClosedOrbitBeamPx,ClosedOrbitBeamPy,ClosedOrbitBeamDelta,BeamOffsetX,BeamOffsetY,BeamOffsetSigma,BeamOffsetPx,BeamOffsetPy,BeamOffsetDelta,bbcu11,bbcu12,SigmaNqX,SigmaNqY,SquareOfSigmaNX,SquareOfSigmaNY,SwitchToLinearCoupling,partf);
                break;
        case 2: ret = beambeam_type2_calc(pfstart, x, y, px, py, RatioPtoPj, HorBeamBeamSeparation,VerBeamBeamSeparation,L,ClosedOrbitBeamX,ClosedOrbitBeamY,ClosedOrbitBeamSigma,ClosedOrbitBeamPx,ClosedOrbitBeamPy,ClosedOrbitBeamDelta,BeamOffsetX,BeamOffsetY,BeamOffsetSigma,BeamOffsetPx,BeamOffsetPy,BeamOffsetDelta,bbcu11,bbcu12,SigmaNqX,SigmaNqY,SquareOfSigmaNX,SquareOfSigmaNY,SwitchToLinearCoupling,NoOfParticles,SwitchToFastBeamBeamAlgo,crxbj,crzbj,cbxbj,cbzbj,partf);
                break;
        case 3: ret = beambeam_type3_calc(pfstart, x, y, px, py, RatioPtoPj, HorBeamBeamSeparation,VerBeamBeamSeparation,L,ClosedOrbitBeamX,ClosedOrbitBeamY,ClosedOrbitBeamSigma,ClosedOrbitBeamPx,ClosedOrbitBeamPy,ClosedOrbitBeamDelta,BeamOffsetX,BeamOffsetY,BeamOffsetSigma,BeamOffsetPx,BeamOffsetPy,BeamOffsetDelta,bbcu11,bbcu12,SigmaNqX,SigmaNqY,SquareOfSigmaNX,SquareOfSigmaNY,SwitchToLinearCoupling,NoOfParticles,SwitchToFastBeamBeamAlgo,crxbj,crzbj,cbxbj,cbzbj,partf);
                break;
    }

    return ret;
}

/*int main(){
  INT elemi[]={0,0,2,2,1}; //mapid,mapst,SwitchToLinearCoupling,NoOfParticles,SwitchToFastBeamBeamAlgo,BeambeamType
  FLOAT elemf[]={2.0,0.17,0.45,0.6,0.6,0.3,0.4,0.1,1.0,2.0,2.3,12.0,3.2,4.05,3.6,7.12,5.5,9.0,5.2,4.44};  //HorBeamBeamSeparation,VerBeamBeamSeparation,L,ClosedOrbitBeamX,ClosedOrbitBeamY,ClosedOrbitBeamSigma,ClosedOrbitBeamPx,ClosedOrbitBeamPy,ClosedOrbitBeamDelta,BeamOffsetX,BeamOffsetY,BeamOffsetSigma,BeamOffsetPx,BeamOffsetPy,BeamOffsetDelta,bbcu11,bbcu12,SigmaNqX,SigmaNqY,SquareOfSigmaNX,SquareOfSigmaNY         
  INT parti[]={1,15,0,0,0}; // partn,ndf,ndi,psf,psi
  FLOAT partf[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //p0,beta0,gamma0,m0,E0,x,px,y,py,ct,dp,pt,s,m,q
  INT elemid=0;
  INT partid=0;
  INT partn=0;
  printf("%d\n", beambeam_map(elemi,elemf,elemid,parti,partf,partid,partn));
  return 1;
}*/