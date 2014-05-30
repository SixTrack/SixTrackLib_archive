#include<stdio.h>

extern int thin6d_track_hor_dipole_(double* argf,double *argi,double*coord,int napx)
{
coord[0] = coord[0] + argf[0] * argi[0];
coord[1] = coord[1] + argf[1] * argi[0];
return 1;
}
