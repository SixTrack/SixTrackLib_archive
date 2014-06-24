#include<stdio.h>
#include<math.h>
#include"crlibm/crlibm.h"

#define OnePoweredToMinus38               1.0e-38
#define Zero                              0.0
#define Half                              0.5
#define One                               1.0
#define Two                               2.0
#define Three                             3.0
#define Four                              4.0
#define OnePoweredTo1                     1.0e1
#define OnePoweredTo2                     1.0e2
#define OnePoweredTo3                     1.0e3
#define OnePoweredTo4                     1.0e4
#define OnePoweredTo5      	          1.0e5
#define OnePoweredTo6                     1.0e6
#define OnePoweredTo12                    1.0e12
#define OnePoweredTo13                    1.0e13
#define OnePoweredTo15                    1.0e15
#define OnePoweredTo16                    1.0e16

#define TwoPoweredTo3                     2.0e3
#define FourPoweredTo3                    4.0e3

#define OnePoweredToMinus1                1.0e-1
#define OnePoweredToMinus2                1.0e-2
#define OnePoweredToMinus3                1.0e-3
#define OnePoweredToMinus6                1.0e-6
#define OnePoweredToMinus7                1.0e-7
#define OnePoweredToMinus9                1.0e-9
#define OnePoweredToMinus10               1.0e-10
#define OnePoweredToMinus12               1.0e-12
#define OnePoweredToMinus13               1.0e-13
#define OnePoweredToMinus15               1.0e-15
#define OnePoweredToMinus18               1.0e-18
#define OnePoweredToMinus21               1.0e-21
#define OnePoweredToMinus24               1.0e-24
#define OnePoweredToMinus36               1.0e-36

#define SpeedOfLight_mps                  2.99792458e8
#define RestMastOfProton_MeV              938.271998e0 
#define ClassicalRadiusOfElectron_m       2.817940285e-15
#define RestMassofElectron_MeV            0.510998902e0 
#define Pi                                4.0*atan_rn(1.0)



#define make_map_crab_cavity( I, C ) \
int cntcrabcavity##I = 0;   \
      extern int thin6d_map_crab_cavity_##I##_(double *coord, double *argf, double *argi) \
{ \
double x = coord[0], y = coord[1]; \
double xp = coord[2], yp = coord[3]; \
double RatioPtoPj = coord[4];          \
double PathLengthDiff = coord[5];        \
double EnergyOfParticle = coord[6], MomentumOfParticle = coord[7]; \
double RatioDeltaPtoP = coord[8], RatioDeltaPtoP1 = coord[9];   \
double RatioBetaToBetaj = coord[12];    \
double MomentumOfParticle0 = coord[13];   \
                                                    \
double AmplitudeCrabCavity = argf[91], FrequencyCrabCavity = argf[6], PhaseCrabCavity = argf[92];   \
double FirstAdditionalDatum = argf[9];        \
double RestMassOfParticle = argf[17];         \
double EnergyOfReferenceParticle =argf[14], MomentumOfReferenceParticle = argf[13];   \
                    \
AmplitudeCrabCavity = ( FirstAdditionalDatum / MomentumOfParticle ) * OnePoweredTo3;    \
C##p = C##p - AmplitudeCrabCavity * sin_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity );  \
\
RatioDeltaPtoP = RatioDeltaPtoP - (((((( AmplitudeCrabCavity * FrequencyCrabCavity) * 2.0 ) * Pi ) / SpeedOfLight_mps ) * C ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity ) ) * OnePoweredToMinus3;  \
 \
MomentumOfParticle0 = MomentumOfParticle;  \
MomentumOfParticle = RatioDeltaPtoP * MomentumOfReferenceParticle + MomentumOfReferenceParticle;   \
EnergyOfParticle = sqrt( MomentumOfParticle*MomentumOfParticle + RestMassOfParticle*RestMassOfParticle );  \
RatioPtoPj = One / ( One + RatioDeltaPtoP );     \
RatioDeltaPtoP1 = ( RatioDeltaPtoP * OnePoweredTo3 ) * RatioPtoPj;  \
xp = ( MomentumOfParticle0 / MomentumOfParticle ) * xp;   \
yp = ( MomentumOfParticle0 / MomentumOfParticle ) * yp;   \
RatioBetaToBetaj = ( EnergyOfParticle * MomentumOfReferenceParticle ) / ( EnergyOfReferenceParticle * MomentumOfParticle );  \
\
coord[2] = xp;    coord[3] = yp;  \
coord[4] = RatioPtoPj;             \
coord[6] = EnergyOfParticle;  coord[7] = MomentumOfParticle; coord[13] = MomentumOfParticle0;  \
coord[8] = RatioDeltaPtoP;    coord[9] = RatioDeltaPtoP1;   \
coord[12] = RatioBetaToBetaj;      \
\
cntcrabcavity##I++;   \
printf("Crab Cavity##I called %d times\n",cntcrabcavity##I);   \
return 1;   \
}; \

make_map_crab_cavity(1,x);
make_map_crab_cavity(2,y);