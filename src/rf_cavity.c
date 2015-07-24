#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define rf_cavity_TYPE                                          6
#define rf_cavity_float_dppoff                                  0
#define rf_cavity_float_ElementType                             1
#define rf_cavity_float_FirstAdditionalDatum                    2
#define rf_cavity_float_FrequencyOfCavity                       3
#define rf_cavity_float_LagPhaseOfCavity                        4
#define rf_cavity_float_VoltageOfCavity                         5
#define rf_cavity_float_RFFrequencyOfCavity                     6
#define rf_cavity_float_PathLengthOffset                        7

inline void rf_cavity_track(FLOAT px, FLOAT py, FLOAT ps, FLOAT ds, FLOAT E0, FLOAT p0, FLOAT m0,
                         FLOAT RatioPtoPj, FLOAT RatioDeltaPtoPj1, FLOAT MomentumOfParticle, FLOAT EnergyOfParticle,
                         FLOAT RatioBetaToBetaj, FLOAT MomentumOfParticle0, FLOAT dppoff, FLOAT ElementType, 
                         FLOAT FirstAdditionalDatum, FLOAT FrequencyOfCavity, FLOAT LagPhaseOfCavity, 
                         FLOAT VoltageOfCavity, FLOAT RFFrequencyOfCavity, FLOAT PathLengthOffset, FLOAT coordf[]){

  if( abs( dppoff ) > OnePoweredToMinus38 ) ds  = ds - PathLengthOffset;

    if( ElementType == 12 )
        EnergyOfParticle += FirstAdditionalDatum * sin( FrequencyOfCavity * ds + LagPhaseOfCavity );
    else
        EnergyOfParticle += VoltageOfCavity * sin( RFFrequencyOfCavity * ds );

    MomentumOfParticle = sqrt( EnergyOfParticle*EnergyOfParticle - m0*m0 );
    RatioBetaToBetaj = ( EnergyOfParticle * p0 ) / ( E0 * MomentumOfParticle );
    ps = ( MomentumOfParticle - p0 ) / p0;
    RatioPtoPj = 1.0 / ( 1.0 + ps );
    RatioDeltaPtoPj1 = ( ps * OnePoweredTo3 ) * RatioPtoPj;
    px = ( MomentumOfParticle0 / MomentumOfParticle ) * px;
    py = ( MomentumOfParticle0 / MomentumOfParticle ) * py;

    SETCOORDF(coordf,ps,ps);
    SETCOORDF(coordf,px,px);
    SETCOORDF(coordf,py,py);
}

INT rf_cavity_single(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    FLOAT RatioPtoPj, RatioDeltaPtoPj1, EnergyOfParticle, MomentumOfParticle, RatioBetaToBetaj, MomentumOfParticle0;
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
    GETCOORDF(partf,ps);
    GETCOORDF(partf,ds);
    GETCOORDF(partf,E0);
    GETCOORDF(partf,p0);
    GETCOORDF(partf,m0);

    RatioPtoPj = One / ( One + ps );
    RatioDeltaPtoPj1 = ( ps * OnePoweredTo3 ) * RatioPtoPj;
    MomentumOfParticle = p0 * ( One + ps );
    EnergyOfParticle = sqrt( MomentumOfParticle * MomentumOfParticle + m0 * m0 );
    RatioBetaToBetaj = ( EnergyOfParticle * p0 ) / ( E0 * MomentumOfParticle );
    MomentumOfParticle0 = MomentumOfParticle;

    rf_cavity_track(px, py, ps, ds, E0, p0, m0, RatioPtoPj, RatioDeltaPtoPj1, MomentumOfParticle, EnergyOfParticle, 
        RatioBetaToBetaj, MomentumOfParticle0, dppoff, ElementType, FirstAdditionalDatum, FrequencyOfCavity, LagPhaseOfCavity, 
        VoltageOfCavity, RFFrequencyOfCavity, PathLengthOffset, GETPARTF(partid));
    return 1;
}

INT rf_cavity_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    FLOAT RatioPtoPj, RatioDeltaPtoPj1, EnergyOfParticle, MomentumOfParticle, RatioBetaToBetaj, MomentumOfParticle0;
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
    GETCOORDF(partf,ps);
    GETCOORDF(partf,ds);
    GETCOORDF(partf,E0);
    GETCOORDF(partf,p0);
    GETCOORDF(partf,m0);

    RatioPtoPj = One / ( One + ps );
    RatioDeltaPtoPj1 = ( ps * OnePoweredTo3 ) * RatioPtoPj;
    MomentumOfParticle = p0 * ( One + ps );
    EnergyOfParticle = sqrt( MomentumOfParticle * MomentumOfParticle + m0 * m0 );
    RatioBetaToBetaj = ( EnergyOfParticle * p0 ) / ( E0 * MomentumOfParticle );
    MomentumOfParticle0 = MomentumOfParticle;

    for(;partid<partn;partid++){
      rf_cavity_track(px, py, ps, ds, E0, p0, m0, RatioPtoPj, RatioDeltaPtoPj1, MomentumOfParticle, EnergyOfParticle, 
        RatioBetaToBetaj, MomentumOfParticle0, dppoff, ElementType, FirstAdditionalDatum, FrequencyOfCavity, LagPhaseOfCavity, 
        VoltageOfCavity, RFFrequencyOfCavity, PathLengthOffset, GETPARTF(partid));
    };
    return 1;
}