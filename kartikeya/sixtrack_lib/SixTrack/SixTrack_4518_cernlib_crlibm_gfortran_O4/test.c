#include<stdio.h>

#define coord(i) coord[i-1]
#define argf(i)  argf[i-1]
#define argi(i)  argi[i-1]

extern int map_hr_2_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[2*argi[0]+j-1]+=argf[0]*coord[6*argi[0]+j-1];
coord[3*argi[0]+j-1]+=argf[1]*coord[6*argi[0]+j-1];
}
return 1;
}

extern int map_thin6d_quadrupole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord(4*argi[0]+j)=(coord(j)-argf(3))*argf(5)+(coord(argi[0]+j)-argf(4))*argf(6);
coord(5*argi[0]+j)=(coord(argi[0]+j)-argf(4))*argf(5)-(coord(j)-argf(3))*argf(6) ;                                
argf(7)=coord(4*argi[0]+j);
argf(8)=coord(5*argi[0]+j);
coord[2*argi[0]+j-1]+=coord[6*argi[0]+j-1]*(argf[0]*argf(7)+argf[1]*argf(8));
coord[3*argi[0]+j-1]+=coord[6*argi[0]+j-1]*(argf[1]*argf(7)-argf[0]*argf(8)) ;  
}                                               
return 1;
}

extern int mp(double *v1,double *v2,double *v3,double *v4,double *v5,double *v6,double *v7)
{
*v1 = (*v2-(*v3))*(*v4)+(*v5-(*v6))*(*v7);
return 1;
}

extern int mp1(double *var1,double *var2,double *var3,double *argf)
{
*var1=(*var2-argf[9])*argf[11]+(*var3-argf[10])*argf[12];
return 1;
}
/*
//<<<<<<< HEAD

extern int thin6d_track1_(double *yv,double *var1,double *var2,int *n)
{
int i;
FILE *fp = fopen("tempo1","w");
fprintf(fp,"value of yv - %40.20f\n value of var1 - %40.20f\n value of var2 - %40.20f\n value of napx - %d\n",*yv,*var1,*var2,*n);

//for(i=1;i<=(*n);i++)
//*yv += (*var1)*(*var2);
fprintf(fp,"value of yv - %40.20f\n",*yv);
fclose(fp);
return 1;
}
extern int thin6d_track2_(double *yv,double *var1,double *var2,int *n)
{
int i;
FILE *fp = fopen("tempo2","w");
fprintf(fp,"value of yv - %40.20f\n value of var1 - %40.20f\n value of var2 - %40.20f\n value of napx - %d\n",*yv,*var1,*var2,*n);

//for(i=1;i<=(*n);i++)
//*yv += (*var1)*(*var2);
fprintf(fp,"value of yv - %40.20f\n",*yv);
fclose(fp);
return 1;
}

//extern int thin6d_track_(double *var1,double *var2,double *var3)
//=======
/*extern int thin6d_track_hor_dipole_(double* argf,double *argi,double*coord)
//>>>>>>> 31b687648ee5a8217c5bd2d3f33284b34de5a82b
{
*var1 += (*var2)*(*var3);
return 1;
}

extern int  file_write_(double yv)
{
FILE *fp = fopen("tempo1","w");
fprintf(fp,"%40.20f",yv);
fclose(fp);
}
*/
/*
extern int thin6d_singarray_(double *coord,double *argf,double *argi,int *j)
{
coord[0+(*j)*(*j)]+=argf[0]*argi[(*j)*(*j)];
coord[1+(*j)*(*j)]+=argf[1]*argi[(*j)*(*j)];
return 1;
}
extern int map_thin6d_hor_dipole_(double *coord,double *argf,int *argi)
{
int j;
for(j=1;j<=argi[1];j++)
{
coord[j*j]+=argf[0]*argf[2+j-1];
coord[j*j+1]+=argf[1]*argi[2+j-1];
}
return 1;
}*/

