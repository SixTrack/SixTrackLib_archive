#include<iostream>
#include<stdio.h>
#include<math.h>

class DAvec_6_1{
    public:
        double val[7];
        DAvec_6_1()
        {
            for(int i=0;i<7;i++)
                val[i]=0;
        }
        DAvec_6_1(double values[])
        {
            for(int i=0;i<7;i++)
                val[i] = values[i];            
        }
        DAvec_6_1 inv();
        DAvec_6_1 operator+(const DAvec_6_1& obj);
        DAvec_6_1 operator-();
        DAvec_6_1 operator-(const DAvec_6_1& obj);
        DAvec_6_1 operator*(const DAvec_6_1& obj);
        DAvec_6_1 operator/(const DAvec_6_1& obj);
};

DAvec_6_1 DAvec_6_1::operator*(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj;
    temp_obj.val[0] = (*this).val[0]*obj.val[0];
    for(int i=1;i<7;i++)
        temp_obj.val[i] = (*this).val[0]*obj.val[i]+obj.val[0]*(*this).val[i];
    return temp_obj;
}

DAvec_6_1 DAvec_6_1::operator+(const DAvec_6_1& obj)
{
    for(int i=0;i<7;i++)
        (*this).val[i] += obj.val[i];
    return (*this);
}

DAvec_6_1 DAvec_6_1::operator-()
{
    for(int i=0;i<7;i++)
        (*this).val[i] = -(*this).val[i];
    return (*this);
}

DAvec_6_1 DAvec_6_1::operator-(const DAvec_6_1& obj)
{
    for(int i=0;i<7;i++)
        (*this).val[i] -= obj.val[i];
    return (*this);
}

DAvec_6_1 DAvec_6_1::operator/(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj = obj;
    return (*this)*temp_obj.inv();
}

DAvec_6_1 DAvec_6_1::inv()
{
    DAvec_6_1 temp_obj;
    temp_obj.val[0]=1/(*this).val[0];
    for(int i=1;i<7;i++)
        temp_obj.val[i]=-(*this).val[i]/((*this).val[0]*(*this).val[0]);
    return temp_obj;
}

DAvec_6_1 acos(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj;
    double a0 = obj.val[0];
    temp_obj.val[0] = ::acos(a0);
    for(int i=1;i<7;i++)
        temp_obj.val[i] = -obj.val[i]/::sin(temp_obj.val[0]);
    return temp_obj;
}

DAvec_6_1 asin(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj;
    double a0 = obj.val[0];
    temp_obj.val[0] = ::asin(a0);
    for(int i=1;i<7;i++)
        temp_obj.val[i] = obj.val[i]/::cos(temp_obj.val[0]);
    return temp_obj;
}

DAvec_6_1 cosh(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj;
    double a0 = obj.val[0];
    temp_obj.val[0] = ::cosh(a0);
    for(int i=1;i<7;i++)
        temp_obj.val[i] = ::sinh(a0)*obj.val[i];
    return temp_obj;
}

DAvec_6_1 sinh(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj;
    double a0 = obj.val[0];
    temp_obj.val[0] = ::sinh(a0);
    for(int i=1;i<7;i++)
        temp_obj.val[i] = ::cosh(a0)*obj.val[i];
    return temp_obj;
}

DAvec_6_1 cos(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj;
    double a0 = obj.val[0];
    temp_obj.val[0] = ::cos(a0);
    for(int i=1;i<7;i++)
        temp_obj.val[i] = -::sin(a0)*obj.val[i];
    return temp_obj;
}

DAvec_6_1 sin(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj;
    double a0 = obj.val[0];
    temp_obj.val[0] = ::sin(a0);
    for(int i=1;i<7;i++)
        temp_obj.val[i] = ::cos(a0)*obj.val[i];
    return temp_obj;
}

DAvec_6_1 sqrt(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj;
    double a0 = obj.val[0];
    temp_obj.val[0] = ::sqrt(a0);
    for(int i=1;i<7;i++)
        temp_obj.val[i] = obj.val[i]/(2*(::sqrt(a0)));
    return temp_obj;
}

DAvec_6_1 exp(const DAvec_6_1& obj)
{
    DAvec_6_1 temp_obj;
    double a0 = obj.val[0];
    temp_obj.val[0] = ::exp(a0);
    for(int i=1;i<7;i++)
        temp_obj.val[i] = ::exp(a0)*obj.val[i];
    return temp_obj;
}

#define RealT DAvec_6_1
#include "maps.c"

//for checking
using namespace std;
int main()
{
    double arr[]={2.07345,0,0,0,0,0,0}, arr1[]={0.02,0,0,0,0,0,0}, arr2[]={0.01,0,0,0,0,0,0},arr3[]={1,0,0,0,0,0,0};
    
    DAvec_6_1 angle(arr),sin_ang,cos_ang;
    sin_ang = sin(angle);
    cos_ang = cos(angle);
    
    int datai[] = {0, 1, 0, 4, 4, 2, 3, 9, 2, 9, 2, 4, 14, 3, 14, 3, 5, 0, 10, 1};
	DAvec_6_1 dataf[] = {angle,sin_ang,cos_ang,DAvec_6_1(arr1),DAvec_6_1(arr2)};
    DAvec_6_1 coord[] = {DAvec_6_1(arr3),DAvec_6_1(arr3)};
    
    map_rot2d(dataf,datai,0,coord);
    return 0;
}









