#include<stdio.h>
#include"crlibm/crlibm.h"
int main()
{
double x,y,z,w;
x=1.0;
y=sin_rn(x);
z=cos_rn(x);
w=tan_rn(x);
printf("%.20f  %.20f  %.20f  %f\n",w,y,y,x);
}
