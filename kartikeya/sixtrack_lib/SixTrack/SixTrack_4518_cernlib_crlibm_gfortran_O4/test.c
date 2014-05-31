#include<stdio.h>

<<<<<<< HEAD

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

extern int thin6d_track_(double *var1,double *var2,double *var3)
=======
extern int thin6d_track_hor_dipole_(double* argf,double *argi,double*coord)
>>>>>>> 31b687648ee5a8217c5bd2d3f33284b34de5a82b
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

extern int thin6d_singarray_(double *coord,double *argf,double *argi)
{
coord[0]+=argf[0]*argi[0];
coord[1]+=argf[1]*argi[0];
return 1;
}

