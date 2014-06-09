#include<stdio.h>
#include<math.h>

extern int thin6d_map_horizontal_dipole_(double *coord, double *argf, double *argi)
{
double xp = coord[2],yp = coord[3];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double RatioPtoPj = coord[4];

coord[2] = xp + LengthElementTiltCos * RatioPtoPj;
coord[3] = yp + LengthElementTiltSin * RatioPtoPj;

return 1;
}

extern int thin6d_map_normal_quadrupole_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2],yp = coord[3];
double RatioPtoPj = coord[4];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double xlvj, zlvj;
double crkve, cikve;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 
crkve = xlvj;
cikve = zlvj;
coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );

return 1;
}

extern int thin6d_map_normal_sextupole_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2],yp = coord[3];
double RatioPtoPj = coord[4];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double xlvj, zlvj;
double crkve, cikve, crkveuk;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 
crkve = xlvj;
cikve = zlvj;
crkveuk = crkve * xlvj - cikve * zlvj;
cikve = crkve * zlvj + cikve * xlvj;
crkve = crkveuk;
coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );

return 1;
}

extern int thin6d_map_normal_octupole_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2],yp = coord[3];
double RatioPtoPj = coord[4];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double xlvj, zlvj;
double crkve, cikve, crkveuk; 
int i;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 
crkve = xlvj;
cikve = zlvj;
for(i=0 ;i < 2 ;i++)
{
crkveuk = crkve * xlvj - cikve * zlvj;
cikve = crkve * zlvj + cikve * xlvj;
crkve = crkveuk;
}

coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );

return 1;
}

extern int thin6d_map_normal_decapole_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2],yp = coord[3];
double RatioPtoPj = coord[4];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double xlvj, zlvj;
double crkve, cikve, crkveuk;
int i;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 
crkve = xlvj;
cikve = zlvj;
for(i=0 ;i < 3 ;i++)
{
crkveuk = crkve * xlvj - cikve * zlvj;
cikve = crkve * zlvj + cikve * xlvj;
crkve = crkveuk;
}

coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );

return 1;
}

extern int thin6d_map_normal_dodecapole_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2],yp = coord[3];
double RatioPtoPj = coord[4];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double xlvj, zlvj;
double crkve, cikve, crkveuk;
int i;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 
crkve = xlvj;
cikve = zlvj;
for(i=0 ;i < 4 ;i++)
{
crkveuk = crkve * xlvj - cikve * zlvj;
cikve = crkve * zlvj + cikve * xlvj;
crkve = crkveuk;
}

coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );

return 1;
}

extern int thin6d_map_normal_14pole_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2],yp = coord[3];
double RatioPtoPj = coord[4];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double xlvj, zlvj;
double crkve, cikve, crkveuk;
int i;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 
crkve = xlvj;
cikve = zlvj;
for(i=0 ;i < 5 ;i++)
{
crkveuk = crkve * xlvj - cikve * zlvj;
cikve = crkve * zlvj + cikve * xlvj;
crkve = crkveuk;
}

coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );

return 1;
}

extern int thin6d_map_normal_16pole_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2],yp = coord[3];
double RatioPtoPj = coord[4];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double xlvj, zlvj;
double crkve, cikve, crkveuk;
int i;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 
crkve = xlvj;
cikve = zlvj;
for(i=0 ;i < 6 ;i++)
{
crkveuk = crkve * xlvj - cikve * zlvj;
cikve = crkve * zlvj + cikve * xlvj;
crkve = crkveuk;
}

coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );

return 1;
}

extern int thin6d_map_normal_18pole_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2],yp = coord[3];
double RatioPtoPj = coord[4];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double xlvj, zlvj;
double crkve, cikve, crkveuk;
int i;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 
crkve = xlvj;
cikve = zlvj;
for(i=0 ;i < 7 ;i++)
{
crkveuk = crkve * xlvj - cikve * zlvj;
cikve = crkve * zlvj + cikve * xlvj;
crkve = crkveuk;
}

coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );

return 1;
}

extern int thin6d_map_normal_20pole_(double *coord, double *argf, double *argi)
{
double x = coord[0], y = coord[1];
double xp = coord[2],yp = coord[3];
double RatioPtoPj = coord[4];
double LengthElementTiltCos = argf[0], LengthElementTiltSin = argf[1];
double CurrentEntryDisplacementX = argf[2], CurrentEntryDisplacementY = argf[3];
double TiltComponentCos = argf[4], TiltComponentSin = argf[5];
double xlvj, zlvj;
double crkve, cikve, crkveuk;
int i;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos + ( x - CurrentEntryDisplacementX ) * TiltComponentSin; 
crkve = xlvj;
cikve = zlvj;

for(i=0 ;i < 8 ;i++)
{
crkveuk = crkve * xlvj - cikve * zlvj;
cikve = crkve * zlvj + cikve * xlvj;
crkve = crkveuk;
}

coord[2] = xp + RatioPtoPj * ( LengthElementTiltCos * crkve + LengthElementTiltSin * cikve );
coord[3] = yp + RatioPtoPj * ( LengthElementTiltSin * crkve - LengthElementTiltCos * cikve );

return 1;
}

extern int thin6d_map_jbg_rf_cc_multipoles_(double *coord, double *argf, double *argi)
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
double SpeedOfLight = argf[12];
double Pi = argf[15];
double OnePoweredTo3 = argf[11], OnePoweredToMinus3 = argf[16];
double EnergyOfReferenceParticle = argf[14], MomentumOfReferenceParticle = argf[13];
double FirstAdditionalDatum = argf[9], SecondAdditionalDatum = argf[10];
double RestMassOfParticle = argf[17];
double xlvj, zlvj;
double crkve, cikve, crkveuk;

xlvj = ( x - CurrentEntryDisplacementX ) * TiltComponentCos + ( y - CurrentEntryDisplacementY ) * TiltComponentSin;
zlvj = ( y - CurrentEntryDisplacementY ) * TiltComponentCos - ( x - CurrentEntryDisplacementX ) * TiltComponentSin;
crkve = xlvj;
cikve = zlvj;
coord[2] = xp + (( AmplitudeCrabCavity2 * crkve ) * RatioPtoPj ) * cos_rn(((( PathLengthDiff / SpeedOfLight ) * FrequencyCrabCavity ) * 2.0 ) * Pi +  PhaseCrabCavity2 );
coord[3] = yp - (( AmplitudeCrabCavity2 * cikve ) * RatioPtoPj ) * cos_rn(((( PathLengthDiff / SpeedOfLight ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity2 );
xp = coord[2];
yp = coord[3];
coord[8] = RatioDeltaPtoP - (((( 0.5 * ( AmplitudeCrabCavity2 * RatioPtoPj )) * ( crkve*crkve - cikve*cikve )) * ((( FrequencyCrabCavity * 2.0 ) * Pi ) / SpeedOfLight )) * OnePoweredToMinus3 ) * sin_rn(((( PathLengthDiff / SpeedOfLight ) * FrequencyCrabCavity ) * 2.0 ) * Pi + PhaseCrabCavity2 );
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
