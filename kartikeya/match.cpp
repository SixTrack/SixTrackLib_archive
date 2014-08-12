#include<iostream>
#include<fstream>
using namespace std;

int main()
{
ifstream in1("fort.6"), in2("fort1.6");
ofstream out1("out1.txt"), out2("out2.txt");

char c2,c1;
while(in1>>c1 && in2>>c2)
if(c1!=c2)
{
out1<<c1;
out2<<c2;
}
}
