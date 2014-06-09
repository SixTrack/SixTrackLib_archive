#include<stdio.h>

#define coord(i) coord[i-1]
#define argf(i)  argf[i-1]
#define argi(i)  argi[i-1]
#define npart 0
#define napx 1
#define strackc 0
#define stracks 1
#define xsiv 2
#define zsiv 3
#define tiltc 4
#define tilts 5
#define crkve 6
#define cikve 7
#define xv(i,j) (i-1)*argi[npart]+j-1
#define yv(i,j) (2+i-1)*argi[npart]+j-1
#define xlv(j) 4*argi[npart]+j-1
#define zlv(j) 5*argi[npart]+j-1
#define oidpsv(j) 6*argi[npart]+j-1

extern int thin6d_map_quadrupole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}
extern int thin4d_map_quadrupole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}
extern int thin6d_map_horizontal_dipole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[2*argi[0]+j-1]+=argf[0]*coord[6*argi[0]+j-1];
coord[3*argi[0]+j-1]+=argf[1]*coord[6*argi[0]+j-1];
}
return 1;
}

extern int thin4d_map_horizontal_dipole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[2*argi[0]+j-1]+=argf[0]*coord[6*argi[0]+j-1];
coord[3*argi[0]+j-1]+=argf[1]*coord[6*argi[0]+j-1];
}
return 1;
}

extern thin6d_map_sextupole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}

extern thin6d_map_norm_octupole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}

extern thin6d_map_norm_decapole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}

extern thin6d_map_norm_dodecapole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}

extern thin6d_map_norm_14pole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}

extern thin6d_map_norm_16pole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}

extern thin6d_map_norm_18pole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}


extern thin6d_map_norm_20pole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
argf[8]=argf[6]*coord[4*argi[npart]+j-1]-argf[7]*coord[5*argi[npart]+j-1];
argf[7]=argf[6]*coord[5*argi[npart]+j-1]+argf[7]*coord[4*argi[npart]+j-1];
argf[6]=argf[8];
coord[2*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[0]*argf[6]+argf[1]*argf[7]);
coord[3*argi[npart]+(j)-1]+=coord[6*argi[npart]+(j)-1]*(argf[1]*argf[6]-argf[0]*argf[7]);
}
return 1;
}

extern int test_(double *pi)
{
*pi=4.0*atan_rn(1.0);
return 1;
}

extern int thin6d_jbgrfcc_multipole_(double *coord,double *argf,double *argi)
{
argf[17]=4.0*atan_rn(1.0);
argf[18]=argf[9];
argf[10]=argf[11]*argf[12];

int j;
for(j=1;j<=argi[1];j++)
{
coord[4*argi[npart]+(j)-1]=(coord[j-1]-argf[2])*argf[4]+(coord[argi[0]+(j)-1]-argf[3])*argf[5];
coord[5*argi[npart]+(j)-1]=(coord[j+argi[0]-1]-argf[3])*argf[4]-(coord[(j)-1]-argf[2])*argf[5];
argf[6]=coord[4*argi[npart]+(j)-1];
argf[7]=coord[5*argi[npart]+(j)-1];
return 1;
}

