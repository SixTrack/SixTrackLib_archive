#include<stdio.h>

#define yv(i,j) yv[j-1][i-1]
#define stracks(i) stracks[i-1]
#define strackc(i) strackc[i-1]
#define oidpsv(j) oidpsv[j-1]

extern struct
{
int npart,i,j,nblz;
}exact_;

extern struct
{
double *stracks,*strackc;
}main4_;

extern struct
{
double *oidpsv;
}main2_;

extern struct
{
double **yv;
}main1_;

extern struct
{
int napx;
}tra1_;



extern void track_hor_dipole_(double* argf,double *argi,double*coord)
{
int k=1;
FILE *fp=fopen("k.txt","w");
for(k = 1; k <= tra1_.napx; ++k)
{
coord[1]=main1_.yv(1,exact_.j)-argf[0]* main2_.oidpsv(exact_.j);
main1_.yv(2,exact_.j)=main1_.yv(2,exact_.j)+argf[1]* main2_.oidpsv(exact_.j);
}
fprintf(fp,"my name");
fclose(fp);

}
