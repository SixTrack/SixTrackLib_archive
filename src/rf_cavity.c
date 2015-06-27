#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

// void print_var(INT [], FLOAT [], INT [], FLOAT [], INT);

inline void rf_cavity_calc(){
}

INT rf_cavity_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    ELEMINIT;
    INITPARTF;

    GETATTRF(rf_cavity,dppoff);
    GETATTRF(rf_cavity,ElementType);
    GETATTRF(rf_cavity,FirstAdditionalDatum);
    GETATTRF(rf_cavity,FrequencyOfCavity);
    GETATTRF(rf_cavity,LagPhaseOfCavity);
    GETATTRF(rf_cavity,VoltageOfCavity);
    GETATTRF(rf_cavity,RFFrequencyOfCavity);
    GETATTRF(rf_cavity,PathLengthOffset);

    GETCOORDF(partf,px);
    GETCOORDF(partf,py);
    GETCOORDF(partf,RatioPtoPj);
    GETCOORDF(partf,ds);
    GETCOORDF(partf,EnergyOfParticle);
    GETCOORDF(partf,MomentumOfParticle);
    GETCOORDF(partf,RatioDeltaPtoPj);
    GETCOORDF(partf,RatioDeltaPtoPj1);
    GETCOORDF(partf,RatioBetaToBetaj);
    GETCOORDF(partf,MomentumOfParticle0);
    GETCOORDF(partf,E0);
    GETCOORDF(partf,p0);
    GETCOORDF(partf,m0);

    MomentumOfParticle0 = MomentumOfParticle;
    if( abs( dppoff ) > OnePoweredToMinus38 ) ds  = ds - PathLengthOffset;

    if( ElementType == 12 )
        EnergyOfParticle += FirstAdditionalDatum * sin( FrequencyOfCavity * ds + LagPhaseOfCavity );
    else
        EnergyOfParticle += VoltageOfCavity * sin( RFFrequencyOfCavity * ds );

    MomentumOfParticle = sqrt( EnergyOfParticle*EnergyOfParticle - m0*m0 );
    RatioBetaToBetaj = ( EnergyOfParticle * p0 ) / ( E0 * MomentumOfParticle );
    RatioDeltaPtoPj = ( MomentumOfParticle - p0 ) / p0;
    RatioPtoPj = 1.0 / ( 1.0 + RatioDeltaPtoPj );
    RatioDeltaPtoPj1 = ( RatioDeltaPtoPj * OnePoweredTo3 ) * RatioPtoPj;
    px = ( MomentumOfParticle0 / MomentumOfParticle ) * px;
    py = ( MomentumOfParticle0 / MomentumOfParticle ) * py;

    SETCOORDF(partf,RatioDeltaPtoPj1,RatioDeltaPtoPj1);
    SETCOORDF(partf,RatioPtoPj,RatioPtoPj);
    SETCOORDF(partf,RatioDeltaPtoPj,RatioDeltaPtoPj);
    SETCOORDF(partf,RatioBetaToBetaj,RatioBetaToBetaj);
    SETCOORDF(partf,MomentumOfParticle,MomentumOfParticle);
    SETCOORDF(partf,px,px);
    SETCOORDF(partf,py,py);
    // print_var(elemi, elemf, parti, partf, rot2d_TYPE);
    return 1;
}