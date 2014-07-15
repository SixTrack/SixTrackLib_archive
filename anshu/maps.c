#include<stdio.h>
#ifndef RealT
typedef double RealT;
#include<math.h>
#endif


int map_rot2d(RealT dataf[], int datai[], int elem_id, RealT coord[]) 
{
  RealT cx,sx,x,y;
  int elem_floatid;
  elem_floatid=datai[elem_id+2];
  cx=dataf[elem_floatid+1]; 
  sx=dataf[elem_floatid+2];
  x=coord[0]; y=coord[1];
  coord[0]= cx*x+sx*y;
  coord[1]= cx*y-sx*x;
 //checking
  int i;
  for(i=0;i<7;i++)
      printf("%lf ",coord[0].val[i]);
  printf("\n");
  for(i=0;i<7;i++)
      printf("%lf ",coord[1].val[i]);
  printf("\n");
 return 1;
};
