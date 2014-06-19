#include<stdio.h>

#define make_fun(name,i) \
    int f##name(int a){ \
         return a+i;    \
        };

make_fun(un1,2);

make_fun(un2,3);

int main()
{
int a=5;
printf("%d\n",fun1(a));
printf("%d\n",fun2(a));
}
