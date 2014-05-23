#include<stdio.h>

#define yv(i,j) yv[j-1][i-1]
#define stracks(i) stracks[i-1]
#define strackc(i) strackc[i-1]
#define oidpsv(j) oidpsv[j-1]

extern struct
{
int j, napx, npart, nblz,i;
double **yv;
double *stracks;
double *strackc;
double *oidpsv;
} ijk_;

void track_vert_dipole_()
{
int k=1;
for(k = 1; k <= ijk_.napx; ++k)
{
ijk_.yv(1,ijk_.j)=ijk_.yv(1,ijk_.j)-ijk_.stracks(ijk_.i)* ijk_.oidpsv(ijk_.j);
ijk_.yv(2,ijk_.j)=ijk_.yv(2,ijk_.j)+ijk_.strackc(ijk_.i)* ijk_.oidpsv(ijk_.j);
}
}
