#include<stdio.h>
#include<math.h>

#define OnePoweredToMinus38               1.0e-38
#define zero                              0.0
#define half                              0.5
#define one                               1.0
#define two                               2.0
#define three                             3.0
#define four                              4.0
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

#define make_map_horizontal_dipole(NAME) \
        int cnt##NAME##hordipole = 0;     \
    extern int NAME##_map_horizontal_dipole_(double *coord, double *argf, double *argi) \
       {   \
         double xp = coord[2],yp = coord[3];  \
         double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];  \
         double RatioPtoPj = coord[4];   \
                                                                 \
         coord[2] = xp + LengthElementTiltCos * RatioPtoPj;        \
         coord[3] = yp + LengthElementTiltSin * RatioPtoPj;       \
                                                                 \
         if(cnt##NAME##hordipole++ ==0)                         \
            printf("NAME hor dipole\n");             \
         return 1;                              \
        }                                               \

#define make_map_normal_pole(NAME,i)  \
int cntnorm##NAME = 0;            \
                                \
extern int thin6d_map_normal_##NAME##_(double *coord, double *argf, double *argi)    \
{                                                          \
double x = coord[0], y = coord[1];            \
double xp = coord[2],yp = coord[3];              \
double RatioPtoPj = coord[4];                                      \
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];                   \
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];          \
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];				\
double xlvj, zlvj;										\
double crkve, cikve, crkveuk;												\
int k = 0;														\
xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;	\
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 	\
crkve = xlvj;													\
cikve = zlvj;													\
for( k = 0; k < i ;k++)												\
{														\
crkveuk = crkve * xlvj - cikve * zlvj;										\
cikve = crkve * zlvj + cikve * xlvj;										\
crkve = crkveuk;												\
}														\
coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );			\
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );			\
														\
/*cntnorm##NAME++;												\
printf("norm called %d times\n",cntnorm##NAME);		*/						\
return 1;													\
}								\

#define make_map_skew_pole(NAME,i)  \
int cntskew##NAME = 0;            \
                                \
extern int thin6d_map_skew_##NAME##_(double *coord, double *argf, double *argi)    \
{                                                          \
double x = coord[0], y = coord[1];            \
double xp = coord[2],yp = coord[3];              \
double RatioPtoPj = coord[4];                                      \
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];                   \
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];          \
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];				\
double xlvj, zlvj;										\
double crkve, cikve, crkveuk;												\
int k = 0;														\
xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;	\
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 	\
crkve = xlvj;													\
cikve = zlvj;													\
for( k = 0; k < i ;k++)												\
{														\
crkveuk = crkve * xlvj - cikve * zlvj;										\
cikve = crkve * zlvj + cikve * xlvj;										\
crkve = crkveuk;												\
}														\
coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );			\
coord[3] = yp + RatioPtoPj * ( LengthElementTiltCos * crkve - LengthElementTiltSin * cikve );			\
														\
/*cntnorm##NAME++;												\
//printf("skew called %d times\n",cntnorm##NAME);	*/							\
return 1;													\
}								\
/*
#define make_map_thin6d_jbgrfcc_multipoles_(NAME,i) \
extern int thin6d_map_jbgrfcc_multipoles_##NAME##_##i##_(double *coord, double *argf, double *argi)  \
{ 													\
double x = coord[0], y = coord[1];										\
double xp = coord[2], yp = coord[3];										\
double RatioPtoPj = coord[4];											\
double PathLengthDiff = coord[5];										\
double EnergyOfParticle = coord[6], MomentumOfParticle = coord[7];						\
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9], OnePlusRatioDeltaPtoP = coord[10], SqrtRatioDeltaPtoP = coord[11];	\
double RatioBetaToBetaj = coord[12];										\
double MomentumOfParticle0 = coord[13];											\
														\
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];		         			\
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];       	  				\
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];					      			\
double FrequencyCrabCavity = argf[6], AmplitudeCrabCavity2 = argf[7], PhaseCrabCavity2 = argf[8];			\
double EnergyOfReferenceParticle = argf[14], MomentumOfReferenceParticle = argf[13];					\
double FirstAdditionalDatum = argf[9], SecondAdditionalDatum = argf[10];						\
double RestMassOfParticle = argf[17];										\
double xlvj, zlvj;												\
double crkve, cikve, crkveuk;											\
																\
xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;		\
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;		\
crkve = xlvj;															\
cikve = zlvj;											\
coord[3] = yp + (2*i-3) (( AmplitudeCrabCavity2 * cikve ) * RatioPtoPj ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity2 );				\
coord[2] = xp + (( AmplitudeCrabCavity2 * crkve ) * RatioPtoPj ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi +  PhaseCrabCavity2 );				\
xp = coord[2];										\
yp = coord[3];									\
coord[8] = RatioDeltaPtoP - (((( 0.5*i* ( AmplitudeCrabCavity2 * RatioPtoPj )) * ( crkve*crkve )) * ((( FrequencyCrabCavity * 2.0 ) * Pi ) / SpeedOfLight_mps )) * OnePoweredToMinus3 ) * sin_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity2 );									\
RatioDeltaPtoP = coord[8];									\
coord[13] = MomentumOfParticle;								\
MomentumOfParticle0 = coord[13];								  \
coord[7] = RatioDeltaPtoP * MomentumOfReferenceParticle + MomentumOfReferenceParticle;		  \
MomentumOfParticle = coord[7];								           \
coord[6] = sqrt( MomentumOfParticle*MomentumOfParticle + RestMassOfParticle*RestMassOfParticle );     \
EnergyOfParticle = coord[6];										\
coord[4] = 1.0 / ( 1.0 + RatioDeltaPtoP );					\
RatioPtoPj = coord[4];												\
coord[9] = ( RatioDeltaPtoP * OnePoweredTo3 ) * RatioPtoPj;					\
RatioDeltaPtoPj1 = coord[9];										\
coord[2] = ( MomentumOfParticle0 / MomentumOfParticle ) * xp;						\
coord[3] = ( MomentumOfParticle0 / MomentumOfParticle ) * yp;								\
coord[12] = ( EnergyOfParticle * MomentumOfReferenceParticle ) / ( EnergyOfReferenceParticle * MomentumOfParticle );		\
														\
return 1;													\
}									\
*/
#define make_map_multipole_hor_zapprox(NAME)  \
    extern int thin6d_map_multipole_##NAME##_(double *coord, double *argf, double *argi)     \
	{					            	       					\
		double x = coord[0], y = coord[1];							\
		double xp = coord[2], yp = coord[3];							\
		double RatioPtoPj = coord[4];									\
		double PathLengthDiff = coord[5];								\
		double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9];				\
		double RatioBetaToBetaj = coord[12];							\
													\
		double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];				\
		double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];          \
            													\
		double TiltComponentCos = argf[4], TiltComponentSin = argf[5];				\
		double HorizontalBendingKick = argf[32];							\
		double PhysicalLengthOfBlock = argf[33];						\
		double VerticalBendingKick = argf[34];							\
		double xlvj, zlvj;									\
													\
		xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;	\
		zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;	\
		coord[2] = ( xp - LengthElementTiltSin * RatioDeltaPtoPj1 ) + (( OnePoweredTo3 * VerticalBendingKick ) * RatioPtoPj ) *	 TiltComponentSin;															\
		coord[3] = ( yp + LengthElementTiltCos * RatioDeltaPtoPj1 ) - (( OnePoweredTo3 * VerticalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos);														\
		coord[5] = PathLengthDiff - ( RatioBetaToBetaj * VerticalBendingKick ) * zlvj;			\
																\
		return 1;						\
	}					\

#define make_map_multipole_hor_nzapprox(NAME)  \
    extern int thin6d_map_multipole_##NAME##_(double *coord, double *argf, double *argi)     \
	{					            	       					\
		double x = coord[0], y = coord[1];							\
		double xp = coord[2], yp = coord[3];							\
		double RatioPtoPj = coord[4];									\
		double PathLengthDiff = coord[5];								\
		double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9];				\
		double RatioBetaToBetaj = coord[12];							\
													\
		double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];				\
		double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];          \
            													\
		double TiltComponentCos = argf[4], TiltComponentSin = argf[5];				\
		double HorizontalBendingKick = argf[32];							\
		double PhysicalLengthOfBlock = argf[33];						\
		double VerticalBendingKick = argf[34];							\
		double xlvj, zlvj;									\
													\
		xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;	\
		zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;	\
coord[2] = ( xp - ((( PhysicalLengthOfBlock * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentCos ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos );						\
coord[3] = ( yp - ((( PhysicalLengthOfBlock * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentSin ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) *  TiltComponentSin;					\
coord[5] = PathLengthDiff + ( RatioBetaToBetaj * HorizontalBendingKick ) * xlvj;					\
															\
return 1;														\
}															\


#define make_map_multipole_ver_nzapprox(NAME)  \
    extern int thin6d_map_multipole_##NAME##_(double *coord, double *argf, double *argi)     \
	{					            	       					\
		double x = coord[0], y = coord[1];							\
		double xp = coord[2], yp = coord[3];							\
		double RatioPtoPj = coord[4];									\
		double PathLengthDiff = coord[5];								\
		double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9];				\
		double RatioBetaToBetaj = coord[12];							\
													\
		double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];				\
		double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];          \
            													\
		double TiltComponentCos = argf[4], TiltComponentSin = argf[5];				\
		double HorizontalBendingKick = argf[32];							\
		double PhysicalLengthOfBlock = argf[33];						\
		double VerticalBendingKick = argf[34];							\
		double xlvj, zlvj;									\
													\
		xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;	\
		zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;	\
coord[2] = ( xp + ((( PhysicalLengthOfBlock * zlvj ) * RatioPtoPj - RatioDeltaPtoPj1 ) * VerticalBendingKick ) * TiltComponentSin ) + (( OnePoweredTo3 * VerticalBendingKick ) * RatioPtoPj ) * TiltComponentSin;								\
coord[3] = ( yp - ((( PhysicalLengthOfBlock * zlvj ) * RatioPtoPj - RatioDeltaPtoPj1 ) * VerticalBendingKick ) * TiltComponentCos ) - (( OnePoweredTo3 * VerticalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos);			\
coord[5] = PathLengthDiff - ( RatioBetaToBetaj * VerticalBendingKick ) * zlvj;			\
										\
return 1;								\
}							\

//make_map_thin6d_jbgrfcc_multipoles_(order2,1);
//make_map_thin6d_jbgrfcc_multipoles_(order2,2);

make_map_horizontal_dipole( thin4d );
make_map_horizontal_dipole( thin6d );

make_map_normal_pole( quadrupole, 0 );
make_map_normal_pole( sextupole, 1 );
make_map_normal_pole( octupole, 2 );
make_map_normal_pole( decapole, 3 );
make_map_normal_pole( dodecapole, 4 );
make_map_normal_pole( 14pole, 5 );
make_map_normal_pole( 16pole, 6 );
make_map_normal_pole( 18pole, 7 );
make_map_normal_pole( 20pole, 8 );

make_map_skew_pole( quadrupole, 0 );
make_map_skew_pole( sextupole, 1 );
make_map_skew_pole( octupole, 2 );
make_map_skew_pole( decapole, 3 );
make_map_skew_pole( dodecapole, 4 );
make_map_skew_pole( 14pole, 5 );
make_map_skew_pole( 16pole, 6 );
make_map_skew_pole( 18pole, 7 );
make_map_skew_pole( 20pole, 8 );

make_map_multipole_hor_zapprox(hor_zapprox_ho);
make_map_multipole_hor_zapprox(purehor_zapprox);

make_map_multipole_hor_nzapprox(hor_nzapprox_ho);
make_map_multipole_hor_nzapprox(purehor_nzapprox);

make_map_multipole_ver_nzapprox(ver_nzapprox_ho);
make_map_multipole_ver_nzapprox(purever_nzapprox);

int cntdrift = 0, cntnormquad=0, cntskewquad=0, cnthordip=0, cntverdip=0, cntnormsext =0, cntskewsext =0, cntnormoct =0, cntskewoct =0, cntnormdec =0, cntskewdec =0;
extern int thin6d_map_exact_drift_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double EnergyOfParticle = coord[6], MomentumOfParticle = coord[7];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9], OnePlusRatioDeltaPtoP = coord[10], SqrtRatioDeltaPtoP = coord[11];
double RatioBetaToBetaj = coord[12];
double MomentumOfParticle0 = coord[13];

double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double FrequencyCrabCavity = argf[6], AmplitudeCrabCavity4 = argf[21], PhaseCrabCavity4 = argf[22];
double EnergyOfReferenceParticle = argf[14], MomentumOfReferenceParticle = argf[13];
double FirstAdditionalDatum = argf[9], SecondAdditionalDatum = argf[10];
double RestMassOfParticle = argf[17];
double dppoff = argf[24];
double PathLengthOff = argf[26];
double ElementType = argf[27];
double FrequencyOfCavity = argf[28];
double LagPhaseOfCavity = argf[29];
double VoltageOfCavity = argf[30];
double RFFrequencyOfCavity = argf[31];

coord[7] = sqrt( EnergyOfParticle*EnergyOfParticle - RestMassOfParticle*RestMassOfParticle );
MomentumOfParticle = coord[7];
coord[12] = ( EnergyOfParticle * MomentumOfReferenceParticle ) / ( EnergyOfReferenceParticle * MomentumOfParticle );
RatioBetaToBetaj = coord[12];
coord[8] = ( MomentumOfParticle - MomentumOfReferenceParticle ) / MomentumOfReferenceParticle;
RatioDeltaPtoP = coord[8];
coord[4] = 1.0 / ( 1.0 + RatioDeltaPtoP );
RatioPtoPj = coord[4];
coord[9] = ( RatioDeltaPtoP * OnePoweredTo3 ) * RatioPtoPj;
RatioDeltaPtoPj1 = coord[9];

coord[2] = ( MomentumOfParticle0 / MomentumOfParticle ) * xp;
coord[3] = ( MomentumOfParticle0 / MomentumOfParticle ) * yp;

if(cntdrift++ == 0)
printf("thin6d exact drift\n");

return 1;
}


extern int thin6d_map_vertical_dipole_(double *coord, double *argf, double *argi)
{
double xp = coord[2],yp = coord[3];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double RatioPtoPj = coord[4];

coord[2] = xp - LengthElementTiltSin * RatioPtoPj;
coord[3] = yp + LengthElementTiltCos * RatioPtoPj;

if(cntverdip++ ==0)
printf("thin6d ver dipole\n");
return 1;
}

extern int thin6d_map_jbgrfcc_multipoles_order2_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double EnergyOfParticle = coord[6], MomentumOfParticle = coord[7];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9], OnePlusRatioDeltaPtoP = coord[10], SqrtRatioDeltaPtoP = coord[11];
double RatioBetaToBetaj = coord[12];
double MomentumOfParticle0 = coord[13];

double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double FrequencyCrabCavity = argf[6], AmplitudeCrabCavity2 = argf[7], PhaseCrabCavity2 = argf[8];
double EnergyOfReferenceParticle = argf[14], MomentumOfReferenceParticle = argf[13];
double FirstAdditionalDatum = argf[9], SecondAdditionalDatum = argf[10];
double RestMassOfParticle = argf[17];
double xlvj, zlvj;
double crkve, cikve, crkveuk;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
crkve = xlvj;
cikve = zlvj;
coord[2] = xp + (( AmplitudeCrabCavity2 * crkve ) * RatioPtoPj ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi +  PhaseCrabCavity2 );
coord[3] = yp - (( AmplitudeCrabCavity2 * cikve ) * RatioPtoPj ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity2 );
xp = coord[2];
yp = coord[3];
coord[8] = RatioDeltaPtoP - (((( 0.5 * ( AmplitudeCrabCavity2 * RatioPtoPj )) * ( crkve*crkve - cikve*cikve )) * ((( FrequencyCrabCavity * 2.0 ) * Pi ) / SpeedOfLight_mps )) * OnePoweredToMinus3 ) * sin_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity2 );
RatioDeltaPtoP = coord[8];
coord[13] = MomentumOfParticle;
MomentumOfParticle0 = coord[13];
coord[7] = RatioDeltaPtoP * MomentumOfReferenceParticle + MomentumOfReferenceParticle;
MomentumOfParticle = coord[7];
coord[6] = sqrt( MomentumOfParticle*MomentumOfParticle + RestMassOfParticle*RestMassOfParticle );
EnergyOfParticle = coord[6];
coord[4] = 1.0 / ( 1.0 + RatioDeltaPtoP );
RatioPtoPj = coord[4];
coord[9] = ( RatioDeltaPtoP * OnePoweredTo3 ) * RatioPtoPj;
RatioDeltaPtoPj1 = coord[9];
coord[2] = ( MomentumOfParticle0 / MomentumOfParticle ) * xp;
coord[3] = ( MomentumOfParticle0 / MomentumOfParticle ) * yp;
coord[12] = ( EnergyOfParticle * MomentumOfReferenceParticle ) / ( EnergyOfReferenceParticle * MomentumOfParticle );

return 1;
}

extern int thin6d_map_jbgrfcc_multipoles_order2_2_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double EnergyOfParticle = coord[6], MomentumOfParticle = coord[7];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9], OnePlusRatioDeltaPtoP = coord[10], SqrtRatioDeltaPtoP = coord[11];
double RatioBetaToBetaj = coord[12];
double MomentumOfParticle0 = coord[13];

double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double FrequencyCrabCavity = argf[6], AmplitudeCrabCavity2 = argf[7], PhaseCrabCavity2 = argf[8];
double EnergyOfReferenceParticle = argf[14], MomentumOfReferenceParticle = argf[13];
double FirstAdditionalDatum = argf[9], SecondAdditionalDatum = argf[10];
double RestMassOfParticle = argf[17];
double xlvj, zlvj;
double crkve, cikve, crkveuk;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
crkve = xlvj;
cikve = zlvj;
coord[3] = yp + (( AmplitudeCrabCavity2 * cikve ) * RatioPtoPj ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity2 );
coord[2] = xp + (( AmplitudeCrabCavity2 * crkve ) * RatioPtoPj ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi +  PhaseCrabCavity2 );
xp = coord[2];
yp = coord[3];
coord[8] = RatioDeltaPtoP - (((( AmplitudeCrabCavity2 * RatioPtoPj ) * ( crkve*crkve )) * ((( FrequencyCrabCavity * 2.0 ) * Pi ) / SpeedOfLight_mps )) * OnePoweredToMinus3 ) * sin_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity2 );
RatioDeltaPtoP = coord[8];
coord[13] = MomentumOfParticle;
MomentumOfParticle0 = coord[13];
coord[7] = RatioDeltaPtoP * MomentumOfReferenceParticle + MomentumOfReferenceParticle;
MomentumOfParticle = coord[7];
coord[6] = sqrt( MomentumOfParticle*MomentumOfParticle + RestMassOfParticle*RestMassOfParticle );
EnergyOfParticle = coord[6];
coord[4] = 1.0 / ( 1.0 + RatioDeltaPtoP );
RatioPtoPj = coord[4];
coord[9] = ( RatioDeltaPtoP * OnePoweredTo3 ) * RatioPtoPj;
RatioDeltaPtoPj1 = coord[9];
coord[2] = ( MomentumOfParticle0 / MomentumOfParticle ) * xp;
coord[3] = ( MomentumOfParticle0 / MomentumOfParticle ) * yp;
coord[12] = ( EnergyOfParticle * MomentumOfReferenceParticle ) / ( EnergyOfReferenceParticle * MomentumOfParticle );

return 1;
}

extern int thin6d_map_jbgrfcc_multipoles_order3_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double EnergyOfParticle = coord[6], MomentumOfParticle = coord[7];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9], OnePlusRatioDeltaPtoP = coord[10], SqrtRatioDeltaPtoP = coord[11];
double RatioBetaToBetaj = coord[12];
double MomentumOfParticle0 = coord[13];

double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double FrequencyCrabCavity = argf[6], AmplitudeCrabCavity3 = argf[18], PhaseCrabCavity3 = argf[19];
double EnergyOfReferenceParticle = argf[14], MomentumOfReferenceParticle = argf[13];
double FirstAdditionalDatum = argf[9], SecondAdditionalDatum = argf[10];
double RestMassOfParticle = argf[17];
double xlvj, zlvj;
double crkve, cikve, crkveuk;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
crkve = xlvj;
cikve = zlvj;
coord[2] = xp + ((( AmplitudeCrabCavity3 * RatioPtoPj ) * OnePoweredToMinus3) * ( crkve*crkve - cikve*cikve )) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity3 );
coord[3] = yp - (( 2.0*((( AmplitudeCrabCavity3 * crkve )* cikve ) * RatioPtoPj )) * OnePoweredToMinus3 ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity3 );
xp = coord[2];
yp = coord[3];
coord[8] = RatioDeltaPtoP - (((( (1.0/3.0) * ( AmplitudeCrabCavity3 * RatioPtoPj )) * ( crkve*crkve*crkve - ( 3.0*cikve*cikve ) *crkve )) * ((( FrequencyCrabCavity * 2.0 ) * Pi ) / SpeedOfLight_mps )) * OnePoweredToMinus6 ) * sin_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity3 );
RatioDeltaPtoP = coord[8];
coord[13] = MomentumOfParticle;
MomentumOfParticle0 = coord[13];
coord[7] = RatioDeltaPtoP * MomentumOfReferenceParticle + MomentumOfReferenceParticle;
MomentumOfParticle = coord[7];
coord[6] = sqrt( MomentumOfParticle*MomentumOfParticle + RestMassOfParticle*RestMassOfParticle );
EnergyOfParticle = coord[6];
coord[4] = 1.0 / ( 1.0 + RatioDeltaPtoP );
RatioPtoPj = coord[4];
coord[9] = ( RatioDeltaPtoP * OnePoweredTo3 ) * RatioPtoPj;
RatioDeltaPtoPj1 = coord[9];
coord[2] = ( MomentumOfParticle0 / MomentumOfParticle ) * xp;
coord[3] = ( MomentumOfParticle0 / MomentumOfParticle ) * yp;
coord[12] = ( EnergyOfParticle * MomentumOfReferenceParticle ) / ( EnergyOfReferenceParticle * MomentumOfParticle );

return 1;
}

extern int thin6d_map_jbgrfcc_multipoles_order3_2_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double EnergyOfParticle = coord[6], MomentumOfParticle = coord[7];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9], OnePlusRatioDeltaPtoP = coord[10], SqrtRatioDeltaPtoP = coord[11];
double RatioBetaToBetaj = coord[12];
double MomentumOfParticle0 = coord[13];

double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double FrequencyCrabCavity = argf[6], AmplitudeCrabCavity3 = argf[18], PhaseCrabCavity3 = argf[19];
double EnergyOfReferenceParticle = argf[14], MomentumOfReferenceParticle = argf[13];
double FirstAdditionalDatum = argf[9], SecondAdditionalDatum = argf[10];
double RestMassOfParticle = argf[17];
double xlvj, zlvj;
double crkve, cikve, crkveuk;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
crkve = xlvj;
cikve = zlvj;

coord[3] = yp - ((( AmplitudeCrabCavity3 * RatioPtoPj ) * OnePoweredToMinus3 ) * ((cikve*cikve) - (crkve*crkve))) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity3 );
coord[2] = xp + (( 2.0 * ( AmplitudeCrabCavity3 * (crkve * (cikve * RatioPtoPj )))) * OnePoweredToMinus3) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity3 );
xp = coord[2];
yp = coord[3];
coord[8] = RatioDeltaPtoP + (((( (1.0/3.0) * ( AmplitudeCrabCavity3 * RatioPtoPj )) * ( cikve*cikve*cikve - ( 3.0*crkve*crkve ) *cikve )) * ((( FrequencyCrabCavity * 2.0 ) * Pi ) / SpeedOfLight_mps )) * OnePoweredToMinus6 ) * sin_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity3 );
RatioDeltaPtoP = coord[8];
coord[13] = MomentumOfParticle;
MomentumOfParticle0 = coord[13];
coord[7] = RatioDeltaPtoP * MomentumOfReferenceParticle + MomentumOfReferenceParticle;
MomentumOfParticle = coord[7];
coord[6] = sqrt( MomentumOfParticle*MomentumOfParticle + RestMassOfParticle*RestMassOfParticle );
EnergyOfParticle = coord[6];
coord[4] = 1.0 / ( 1.0 + RatioDeltaPtoP );
RatioPtoPj = coord[4];
coord[9] = ( RatioDeltaPtoP * OnePoweredTo3 ) * RatioPtoPj;
RatioDeltaPtoPj1 = coord[9];
coord[2] = ( MomentumOfParticle0 / MomentumOfParticle ) * xp;
coord[3] = ( MomentumOfParticle0 / MomentumOfParticle ) * yp;
coord[12] = ( EnergyOfParticle * MomentumOfReferenceParticle ) / ( EnergyOfReferenceParticle * MomentumOfParticle );

return 1;
}

extern int thin6d_map_jbgrfcc_multipoles_order4_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double EnergyOfParticle = coord[6], MomentumOfParticle = coord[7];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9], OnePlusRatioDeltaPtoP = coord[10], SqrtRatioDeltaPtoP = coord[11];
double RatioBetaToBetaj = coord[12];
double MomentumOfParticle0 = coord[13];

double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double FrequencyCrabCavity = argf[6], AmplitudeCrabCavity4 = argf[21], PhaseCrabCavity4 = argf[22];
double EnergyOfReferenceParticle = argf[14], MomentumOfReferenceParticle = argf[13];
double FirstAdditionalDatum = argf[9], SecondAdditionalDatum = argf[10];
double RestMassOfParticle = argf[17];
double xlvj, zlvj;
double crkve, cikve, crkveuk;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
crkve = xlvj;
cikve = zlvj;
coord[2] = xp + ((( AmplitudeCrabCavity4 * RatioPtoPj ) * ( crkve*crkve*crkve - ( 3.0*crkve )* cikve*cikve )) * OnePoweredToMinus6 ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity4 );
coord[3] = yp - ((( AmplitudeCrabCavity4 * RatioPtoPj ) * (( 3.0*cikve) * crkve*crkve - cikve*cikve*cikve )) * OnePoweredToMinus6 ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity4 );
xp = coord[2];
yp = coord[3];
coord[8] = RatioDeltaPtoP - (((( 0.25 * ( AmplitudeCrabCavity4 * RatioPtoPj )) * ( crkve*crkve*crkve*crkve - ( 6.0*crkve*crkve ) *cikve*cikve + cikve*cikve*cikve*cikve )) * ((( FrequencyCrabCavity * 2.0 ) * Pi ) / SpeedOfLight_mps )) * OnePoweredToMinus9 ) * sin_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity4 );
RatioDeltaPtoP = coord[8];
coord[13] = MomentumOfParticle;
MomentumOfParticle0 = coord[13];
coord[7] = RatioDeltaPtoP * MomentumOfReferenceParticle + MomentumOfReferenceParticle;
MomentumOfParticle = coord[7];
coord[6] = sqrt( MomentumOfParticle*MomentumOfParticle + RestMassOfParticle*RestMassOfParticle );
EnergyOfParticle = coord[6];
coord[4] = 1.0 / ( 1.0 + RatioDeltaPtoP );
RatioPtoPj = coord[4];
coord[9] = ( RatioDeltaPtoP * OnePoweredTo3 ) * RatioPtoPj;
RatioDeltaPtoPj1 = coord[9];
coord[2] = ( MomentumOfParticle0 / MomentumOfParticle ) * xp;
coord[3] = ( MomentumOfParticle0 / MomentumOfParticle ) * yp;
coord[12] = ( EnergyOfParticle * MomentumOfReferenceParticle ) / ( EnergyOfReferenceParticle * MomentumOfParticle );

return 1;
}

extern int thin6d_map_jbgrfcc_multipoles_order4_2_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double EnergyOfParticle = coord[6], MomentumOfParticle = coord[7];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9], OnePlusRatioDeltaPtoP = coord[10], SqrtRatioDeltaPtoP = coord[11];
double RatioBetaToBetaj = coord[12];
double MomentumOfParticle0 = coord[13];

double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double FrequencyCrabCavity = argf[6], AmplitudeCrabCavity4 = argf[21], PhaseCrabCavity4 = argf[22];
double EnergyOfReferenceParticle = argf[14], MomentumOfReferenceParticle = argf[13];
double FirstAdditionalDatum = argf[9], SecondAdditionalDatum = argf[10];
double RestMassOfParticle = argf[17];
double xlvj, zlvj;
double crkve, cikve, crkveuk;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
crkve = xlvj;
cikve = zlvj;
coord[2] = xp + ((( AmplitudeCrabCavity4 * RatioPtoPj ) * ( cikve*cikve*cikve - ( 3.0*cikve )* crkve*crkve )) * OnePoweredToMinus6 ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity4 );
coord[3] = yp + ((( AmplitudeCrabCavity4 * RatioPtoPj ) * (( 3.0*crkve) * cikve*cikve - crkve*crkve*crkve )) * OnePoweredToMinus6 ) * cos_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity4 );
xp = coord[2];
yp = coord[3];
coord[8] = RatioDeltaPtoP - (((( AmplitudeCrabCavity4 * RatioPtoPj ) * (( crkve*crkve*crkve * cikve ) - ( cikve*cikve*cikve * crkve ))) * ((( FrequencyCrabCavity * 2.0 ) * Pi ) / SpeedOfLight_mps )) * OnePoweredToMinus9 ) * sin_rn(((( PathLengthDiff / SpeedOfLight_mps ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity4 );
RatioDeltaPtoP = coord[8];
coord[13] = MomentumOfParticle;
MomentumOfParticle0 = coord[13];
coord[7] = RatioDeltaPtoP * MomentumOfReferenceParticle + MomentumOfReferenceParticle;
MomentumOfParticle = coord[7];
coord[6] = sqrt( MomentumOfParticle*MomentumOfParticle + RestMassOfParticle*RestMassOfParticle );
EnergyOfParticle = coord[6];
coord[4] = 1.0 / ( 1.0 + RatioDeltaPtoP );
RatioPtoPj = coord[4];
coord[9] = ( RatioDeltaPtoP * OnePoweredTo3 ) * RatioPtoPj;
RatioDeltaPtoPj1 = coord[9];
coord[2] = ( MomentumOfParticle0 / MomentumOfParticle ) * xp;
coord[3] = ( MomentumOfParticle0 / MomentumOfParticle ) * yp;
coord[12] = ( EnergyOfParticle * MomentumOfReferenceParticle ) / ( EnergyOfReferenceParticle * MomentumOfParticle );

return 1;
}
/*
extern int thin6d_map_multipole_purehor_nzapprox_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9];
double RatioBetaToBetaj = coord[12];

double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double HorizontalBendingKick = argf[32];
double PhysicalLengthOfBlock = argf[33];
double xlvj, zlvj;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
coord[2] = ( xp - ((( PhysicalLengthOfBlock * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentCos ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos );
coord[3] = ( yp - ((( PhysicalLengthOfBlock * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentSin ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) *  TiltComponentSin;
coord[5] = PathLengthDiff + ( RatioBetaToBetaj * HorizontalBendingKick ) * xlvj;

return 1;
}

extern int thin6d_map_multipole_hor_nzapprox_ho_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9];
double RatioBetaToBetaj = coord[12];

double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double HorizontalBendingKick = argf[32];
double PhysicalLengthOfBlock = argf[33];
double xlvj, zlvj;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
coord[2] = ( xp - ((( PhysicalLengthOfBlock * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentCos ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos );
coord[3] = ( yp - ((( PhysicalLengthOfBlock * xlvj ) * RatioPtoPj + RatioDeltaPtoPj1 ) * HorizontalBendingKick ) * TiltComponentSin ) + (( OnePoweredTo3 * HorizontalBendingKick ) * RatioPtoPj ) *  TiltComponentSin;
coord[5] = PathLengthDiff + ( RatioBetaToBetaj * HorizontalBendingKick ) * xlvj;

return 1;
}
*/
extern int thin6d_map_multipole_purever_zapprox_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9];
double RatioBetaToBetaj = coord[12];

double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double HorizontalBendingKick = argf[32];
double PhysicalLengthOfBlock = argf[33];
double VerticalBendingKick = argf[34];
double xlvj, zlvj;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
coord[2] = ( xp - LengthElementTiltSin * RatioDeltaPtoPj1 ) + (( OnePoweredTo3 * VerticalBendingKick ) * RatioPtoPj ) * TiltComponentSin;
coord[3] = ( yp + LengthElementTiltCos * RatioDeltaPtoPj1 ) - (( OnePoweredTo3 * VerticalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos);
coord[5] = PathLengthDiff - ( RatioBetaToBetaj * VerticalBendingKick ) * zlvj;

return 1;
}

extern int thin6d_map_multipole_ver_zapprox_ho_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double PathLengthDiff = coord[5];
double RatioDeltaPtoP = coord[8], RatioDeltaPtoPj1 = coord[9];
double RatioBetaToBetaj = coord[12];

double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double HorizontalBendingKick = argf[32];
double PhysicalLengthOfBlock = argf[33];
double VerticalBendingKick = argf[34];
double xlvj, zlvj;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
coord[2] = ( xp - LengthElementTiltSin * RatioDeltaPtoPj1 ) + (( OnePoweredTo3 * VerticalBendingKick ) * RatioPtoPj ) * TiltComponentSin;
coord[3] = ( yp + LengthElementTiltCos * RatioDeltaPtoPj1 ) - (( OnePoweredTo3 * VerticalBendingKick ) * RatioPtoPj ) * ( 1.0 - TiltComponentCos);
coord[5] = PathLengthDiff - ( RatioBetaToBetaj * VerticalBendingKick ) * zlvj;

return 1;
}

double sign( double a, double b )
{
if(b >= 0) return abs(a);
else return -abs(a);
}

extern int thin6d_map_beambeam_1_(double *coord, double *argf, double argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];


double PhysicalLengthOfBlock = argf[33];
int SwitchToLinearCoupling = (int)argf[34];
double ClosedOrbitBeamX = argf[35], ClosedOrbitBeamY = argf[36], ClosedOrbitBeamSigma = argf[37], ClosedOrbitBeamPx = argf[38], ClosedOrbitBeamPy = argf[39], ClosedOrbitBeamDelta = argf[40];
double HorBeamBeamSeparation = argf[9], VerBeamBeamSeparation = argf[10];
double SquareOfSigmaN = argf[41];
double BeamOffsetX = argf[42], BeamOffsetY = argf[43], BeamOffsetSigma = argf[44], BeamOffsetPx = argf[45], BeamOffsetPy = argf[46], BeamOffsetDelta = argf[47];
double bbcu11 = argf[48], bbcu12 = argf[49];

double crkvebj, cikvebj, rho2bj, tkbj, cccc;

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

rho2bj = crkvebj*crkvebj + cikvebj*cikvebj;
if( rho2bj <= OnePoweredToMinus38 ) return 1;

tkbj = rho2bj / ( 2.0 * SquareOfSigmaN );
if( SwitchToLinearCoupling == 0 )
{
coord[2] = xp + RatioPtoPj * ((( PhysicalLengthOfBlock * crkvebj ) / rho2bj ) * ( 1.0 - exp_rn( -1.0 * tkbj )) - BeamOffsetPx );
coord[3] = yp + RatioPtoPj * ((( PhysicalLengthOfBlock * cikvebj ) / rho2bj ) * ( 1.0 - exp_rn( -1.0 * tkbj )) - BeamOffsetPy );
}
else
{
cccc = ((( PhysicalLengthOfBlock * crkvebj ) / rho2bj ) * ( 1.0 - exp_rn( -1.0 * tkbj )) - BeamOffsetPx ) * bbcu11 - ((( PhysicalLengthOfBlock * cikvebj ) / rho2bj ) * ( 1.0 - exp_rn( -1.0 * tkbj )) - BeamOffsetPy ) * bbcu12;

coord[2] = xp + RatioPtoPj * cccc;
cccc = ((( PhysicalLengthOfBlock * crkvebj ) / rho2bj ) * ( 1.0 - exp_rn( -1.0 * tkbj )) - BeamOffsetPx ) * bbcu12 - ((( PhysicalLengthOfBlock * cikvebj ) / rho2bj ) * ( 1.0 - exp_rn( -1.0 * tkbj )) - BeamOffsetPy ) * bbcu11;

coord[3] = yp + RatioPtoPj * cccc;
}
printf("beam beam 1\n");
return 1;
}

extern int thin6d_map_beambeam_2_ibtyp_0_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double crxbj = coord[14], crzbj = coord[15];
double cbxbj = coord[16], cbzbj = coord[17];

double SquareRootOfPi = sqrt(argf[15]);

double PhysicalLengthOfBlock = argf[33];
int SwitchToLinearCoupling = (int)argf[34];
double ClosedOrbitBeamX = argf[35], ClosedOrbitBeamY = argf[36], ClosedOrbitBeamSigma = argf[37], ClosedOrbitBeamPx = argf[38], ClosedOrbitBeamPy = argf[39], ClosedOrbitBeamDelta = argf[40];
double HorBeamBeamSeparation = argf[9], VerBeamBeamSeparation = argf[10];
double SquareOfSigmaNX = argf[52], SquareOfSigmaNY = argf[53];
double BeamOffsetX = argf[42], BeamOffsetY = argf[43], BeamOffsetSigma = argf[44], BeamOffsetPx = argf[45], BeamOffsetPy = argf[46], BeamOffsetDelta = argf[47];
double bbcu11 = argf[48], bbcu12 = argf[49];
double SigmaNqX = argf[50], SigmaNqY = argf[51];

double crkvebj, cikvebj, rho2bj, tkbj, cccc, r2bj, rbj, rkbj, xbbj, zbbj, xrbj, zrbj;

r2bj = 2.0 * ( SquareOfSigmaNX - SquareOfSigmaNY );
rbj = sqrt(r2bj);

rkbj = ( PhysicalLengthOfBlock * SquareRootOfPi ) / rbj;

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

errf_( &xrbj, &zrbj, &crxbj, &crzbj );

tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

xbbj = SigmaNqY * xrbj;
zbbj = SigmaNqX * zrbj;

errf_( &xbbj, &zbbj, &cbxbj, &cbzbj );

if( SwitchToLinearCoupling == 0 )
{
coord[2] = xp + RatioPtoPj * (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) *sign( 1.0, crkvebj ) - BeamOffsetPx );
coord[3] = yp + RatioPtoPj * (( rkbj * ( crxbj - exp_rn( -1.0 * tkbj ) * cbxbj )) *sign( 1.0, cikvebj ) - BeamOffsetPy );
}
else
{
cccc = (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu11 - (( rkbj * ( crxbj - exp_rn(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu12;
coord[2] = xp + RatioPtoPj * cccc;

cccc = (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu12 - (( rkbj * ( crxbj - exp_rn(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu11;
coord[3] = yp + RatioPtoPj * cccc;
}

printf("beam beam 2 type 0\n");
return 1;
}

extern int thin6d_map_beambeam_2_ibtyp_1_1_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double crxbj = coord[14], crzbj = coord[15];
double cbxbj = coord[16], cbzbj = coord[17];

double SquareRootOfPi = sqrt(argf[15]);

double PhysicalLengthOfBlock = argf[33];
int SwitchToLinearCoupling = (int)argf[34];
double ClosedOrbitBeamX = argf[35], ClosedOrbitBeamY = argf[36], ClosedOrbitBeamSigma = argf[37], ClosedOrbitBeamPx = argf[38], ClosedOrbitBeamPy = argf[39], ClosedOrbitBeamDelta = argf[40];
double HorBeamBeamSeparation = argf[9], VerBeamBeamSeparation = argf[10];
double SquareOfSigmaNX = argf[52], SquareOfSigmaNY = argf[53];
double BeamOffsetX = argf[42], BeamOffsetY = argf[43], BeamOffsetSigma = argf[44], BeamOffsetPx = argf[45], BeamOffsetPy = argf[46], BeamOffsetDelta = argf[47];
double bbcu11 = argf[48], bbcu12 = argf[49];
double SigmaNqX = argf[50], SigmaNqY = argf[51];
double xbbj = coord[18], zbbj = coord[19]; 
double crkvebj = coord[22], cikvebj = coord[23];
double rkbj = coord[25];
double rho2bj, tkbj, cccc, r2bj, rbj, xrbj, zrbj;

r2bj = 2.0 * ( SquareOfSigmaNX - SquareOfSigmaNY );
rbj = sqrt(r2bj);

rkbj = ( PhysicalLengthOfBlock * SquareRootOfPi ) / rbj;
coord[25] = rkbj;

if( SwitchToLinearCoupling == 0 )
{
crkvebj = ( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation;
cikvebj = ( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation;
coord[22] = crkvebj;
coord[23] = cikvebj;
}
else
{
crkvebj = (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu11 + (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu12;
cikvebj = (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu11 - (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu12;
coord[22] = crkvebj;
coord[23] = cikvebj;
}

xrbj = abs(crkvebj) / rbj;
zrbj = abs(cikvebj) / rbj;

tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

xbbj = SigmaNqY * xrbj;
zbbj = SigmaNqX * zrbj;
coord[18] = xbbj;
coord[19] = zbbj;

return 1;
}

extern int thin6d_map_beambeam_2_ibtyp_1_2_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double crxbj = coord[14], crzbj = coord[15];
double cbxbj = coord[16], cbzbj = coord[17];

double SquareRootOfPi = sqrt(argf[15]);

double PhysicalLengthOfBlock = argf[33];
int SwitchToLinearCoupling = (int)argf[34];
double ClosedOrbitBeamX = argf[35], ClosedOrbitBeamY = argf[36], ClosedOrbitBeamSigma = argf[37], ClosedOrbitBeamPx = argf[38], ClosedOrbitBeamPy = argf[39], ClosedOrbitBeamDelta = argf[40];
double HorBeamBeamSeparation = argf[9], VerBeamBeamSeparation = argf[10];
double SquareOfSigmaNX = argf[52], SquareOfSigmaNY = argf[53];
double BeamOffsetX = argf[42], BeamOffsetY = argf[43], BeamOffsetSigma = argf[44], BeamOffsetPx = argf[45], BeamOffsetPy = argf[46], BeamOffsetDelta = argf[47];
double bbcu11 = argf[48], bbcu12 = argf[49];
double SigmaNqX = argf[50], SigmaNqY = argf[51];
double xbbj = coord[18], zbbj = coord[19]; 
double crkvebj = coord[22], cikvebj = coord[23];
double rkbj = coord[25];
double rho2bj, tkbj, cccc, r2bj, rbj, xrbj, zrbj;

tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;
if( SwitchToLinearCoupling == 0 )
{
coord[2] = xp + RatioPtoPj * (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) *sign( 1.0, crkvebj ) - BeamOffsetPx );
coord[3] = yp + RatioPtoPj * (( rkbj * ( crxbj - exp_rn( -1.0 * tkbj ) * cbxbj )) *sign( 1.0, cikvebj ) - BeamOffsetPy );
}
else
{
cccc = (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu11 - (( rkbj * ( crxbj - exp_rn(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu12;
coord[2] = xp + RatioPtoPj * cccc;

cccc = (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu12 + (( rkbj * ( crxbj - exp_rn(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu11;
coord[3] = yp + RatioPtoPj * cccc;
}

printf("beam beam 2 type 0 2\n");
return 1;
}

extern int thin6d_map_beambeam_3_ibtyp_0_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double crxbj = coord[14], crzbj = coord[15];
double cbxbj = coord[16], cbzbj = coord[17];

double SquareRootOfPi = sqrt(argf[15]);

double PhysicalLengthOfBlock = argf[33];
int SwitchToLinearCoupling = (int)argf[34];
double ClosedOrbitBeamX = argf[35], ClosedOrbitBeamY = argf[36], ClosedOrbitBeamSigma = argf[37], ClosedOrbitBeamPx = argf[38], ClosedOrbitBeamPy = argf[39], ClosedOrbitBeamDelta = argf[40];
double HorBeamBeamSeparation = argf[9], VerBeamBeamSeparation = argf[10];
double SquareOfSigmaNX = argf[52], SquareOfSigmaNY = argf[53];
double BeamOffsetX = argf[42], BeamOffsetY = argf[43], BeamOffsetSigma = argf[44], BeamOffsetPx = argf[45], BeamOffsetPy = argf[46], BeamOffsetDelta = argf[47];
double bbcu11 = argf[48], bbcu12 = argf[49];
double SigmaNqX = argf[50], SigmaNqY = argf[51];

double crkvebj, cikvebj, rho2bj, tkbj, cccc, r2bj, rbj, rkbj, xbbj, zbbj, xrbj, zrbj;

r2bj = 2.0 * ( SquareOfSigmaNY - SquareOfSigmaNX );
rbj = sqrt(r2bj);

rkbj = ( PhysicalLengthOfBlock * SquareRootOfPi ) / rbj;

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

errf_( &zrbj, &xrbj, &crzbj, &crxbj );

tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

xbbj = SigmaNqY * xrbj;
zbbj = SigmaNqX * zrbj;

errf_( &zbbj, &xbbj, &cbzbj, &cbxbj );

if( SwitchToLinearCoupling == 0 )
{
coord[2] = xp + RatioPtoPj * (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) *sign( 1.0, crkvebj ) - BeamOffsetPx );
coord[3] = yp + RatioPtoPj * (( rkbj * ( crxbj - exp_rn( -1.0 * tkbj ) * cbxbj )) *sign( 1.0, cikvebj ) - BeamOffsetPy );
}
else
{
cccc = (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu11 - (( rkbj * ( crxbj - exp_rn(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu12;
coord[2] = xp + RatioPtoPj * cccc;

cccc = (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu12 + (( rkbj * ( crxbj - exp_rn(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu11;
coord[3] = yp + RatioPtoPj * cccc;
}

printf("beam beam 2 type 0\n");
return 1;
}

extern int thin6d_map_beambeam_3_ibtyp_1_1_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double crxbj = coord[14], crzbj = coord[15];
double cbxbj = coord[16], cbzbj = coord[17];

double SquareRootOfPi = sqrt(argf[15]);

double PhysicalLengthOfBlock = argf[33];
int SwitchToLinearCoupling = (int)argf[34];
double ClosedOrbitBeamX = argf[35], ClosedOrbitBeamY = argf[36], ClosedOrbitBeamSigma = argf[37], ClosedOrbitBeamPx = argf[38], ClosedOrbitBeamPy = argf[39], ClosedOrbitBeamDelta = argf[40];
double HorBeamBeamSeparation = argf[9], VerBeamBeamSeparation = argf[10];
double SquareOfSigmaNX = argf[52], SquareOfSigmaNY = argf[53];
double BeamOffsetX = argf[42], BeamOffsetY = argf[43], BeamOffsetSigma = argf[44], BeamOffsetPx = argf[45], BeamOffsetPy = argf[46], BeamOffsetDelta = argf[47];
double bbcu11 = argf[48], bbcu12 = argf[49];
double SigmaNqX = argf[50], SigmaNqY = argf[51];
double xbbj = coord[18], zbbj = coord[19]; 
double crkvebj = coord[22], cikvebj = coord[23];
double rkbj = coord[25];
double rho2bj, tkbj, cccc, r2bj, rbj, xrbj, zrbj;

r2bj = 2.0 * ( SquareOfSigmaNY - SquareOfSigmaNX );
rbj = sqrt(r2bj);

rkbj = ( PhysicalLengthOfBlock * SquareRootOfPi ) / rbj;
coord[25] = rkbj;

if( SwitchToLinearCoupling == 0 )
{
crkvebj = ( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation;
cikvebj = ( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation;
coord[22] = crkvebj;
coord[23] = cikvebj;
}
else
{
crkvebj = (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu11 + (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu12;
cikvebj = (( y - ClosedOrbitBeamY ) + VerBeamBeamSeparation ) * bbcu11 - (( x - ClosedOrbitBeamX ) + HorBeamBeamSeparation ) * bbcu12;
coord[22] = crkvebj;
coord[23] = cikvebj;
}

xrbj = abs(crkvebj) / rbj;
zrbj = abs(cikvebj) / rbj;

tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;

xbbj = SigmaNqY * xrbj;
zbbj = SigmaNqX * zrbj;
coord[18] = xbbj;
coord[19] = zbbj;

return 1;
}

extern int thin6d_map_beambeam_3_ibtyp_1_2_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2], yp = coord[3];
double RatioPtoPj = coord[4];
double crxbj = coord[14], crzbj = coord[15];
double cbxbj = coord[16], cbzbj = coord[17];

double SquareRootOfPi = sqrt(argf[15]);

double PhysicalLengthOfBlock = argf[33];
int SwitchToLinearCoupling = (int)argf[34];
double ClosedOrbitBeamX = argf[35], ClosedOrbitBeamY = argf[36], ClosedOrbitBeamSigma = argf[37], ClosedOrbitBeamPx = argf[38], ClosedOrbitBeamPy = argf[39], ClosedOrbitBeamDelta = argf[40];
double HorBeamBeamSeparation = argf[9], VerBeamBeamSeparation = argf[10];
double SquareOfSigmaNX = argf[52], SquareOfSigmaNY = argf[53];
double BeamOffsetX = argf[42], BeamOffsetY = argf[43], BeamOffsetSigma = argf[44], BeamOffsetPx = argf[45], BeamOffsetPy = argf[46], BeamOffsetDelta = argf[47];
double bbcu11 = argf[48], bbcu12 = argf[49];
double SigmaNqX = argf[50], SigmaNqY = argf[51];
double xbbj = coord[18], zbbj = coord[19]; 
double crkvebj = coord[22], cikvebj = coord[23];
double rkbj = coord[25];
double rho2bj, tkbj, cccc, r2bj, rbj, xrbj, zrbj;

tkbj = ( crkvebj*crkvebj / SquareOfSigmaNX + cikvebj*cikvebj / SquareOfSigmaNY ) * 0.5;
if( SwitchToLinearCoupling == 0 )
{
coord[2] = xp + RatioPtoPj * (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) *sign( 1.0, crkvebj ) - BeamOffsetPx );
coord[3] = yp + RatioPtoPj * (( rkbj * ( crxbj - exp_rn( -1.0 * tkbj ) * cbxbj )) *sign( 1.0, cikvebj ) - BeamOffsetPy );
}
else
{
cccc = (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu11 - (( rkbj * ( crxbj - exp_rn(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu12;
coord[2] = xp + RatioPtoPj * cccc;

cccc = (( rkbj * ( crzbj - exp_rn( -1.0 * tkbj ) * cbzbj )) * sign( 1.0, crkvebj ) - BeamOffsetPx ) * bbcu12 + (( rkbj * ( crxbj - exp_rn(-1.0 * tkbj ) * cbxbj )) * sign( 1.0, cikvebj ) - BeamOffsetPy ) * bbcu11;
coord[3] = yp + RatioPtoPj * cccc;
}

printf("beam beam 3 type 1 2\n");
return 1;
}
