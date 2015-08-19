import mpmath as mp
import matplotlib.pyplot as plt
from numpy import *
import scipy

from wwerf import ccperrfr as wf90
wf90=vectorize(wf90)
# from wwerf2 import errf as wf
# wf=vectorize(wf)

# from mywwerf import wwerf as wpy

from scipy.special import erfc, wofz
mp.dps = 32

# print(mp.quad(lambda x: mp.exp(-x**2), [-mp.inf, mp.inf]) ** 2)

def wofzmp(x,y):
    z=x+1j*y
    w=mp.exp(-z**2) * mp.erfc(z * -1j)
    return w.real,w.imag

wofzmp=vectorize(wofzmp)

def wsci(x,y):
    z=x+1j*y
    w=wofz(z)
    return w.real,w.imag

wsci=vectorize(wsci)

# #https://github.com/PyCOMPLETE/PyHEADTAIL/master/spacecharge/spacecharge.py

# #http://www.bigdft.org/devel-doc/d0/dfa/wofz_8f90_source.html
# #http://www.bigdft.org/devel-doc/d0/dfa/wofz_8f90.html
# #http://dl.acm.org/citation.cfm?id=77629
# # latest
# #www.ccsenet.org/journal/index.php/jmr/article/viewFile/41877/24151 
# # http://ab-initio.mit.edu/wiki/index.php/Faddeeva_Package
# # arxiv.org/pdf/1407.0748 In root with source code


r=15
xx=10**linspace(-r,r,31)
yy=10**linspace(-r,r,31)
x,y=meshgrid(xx,yy)

x1,y1=array(wsci(x,y),dtype=float)
x2,y2=wf90(x,y)
# # x3,y3=wf(x,y)
x4,y4=array(wofzmp(x,y),dtype=float)
# print shape(x1)
for i in range(0,31):
	for j in range(0,31):
		print "%-6s %23.16e %23.16e %23.16e"%("real",sqrt((x2[i][j]-x1[i][j])**2),x2[i][j],x1[i][j])
		print "%-6s %23.16e %23.16e %23.16e\n"%("imag",sqrt((y2[i][j]-y1[i][j])**2),y2[i][j],y1[i][j])
		# print "%-6s %23.16e %23.16e %23.16e"%("real",sqrt((x4[i][j]-x1[i][j])**2),x4[i][j],x1[i][j])
		# print "%-6s %23.16e %23.16e %23.16e\n"%("imag",sqrt((y4[i][j]-y1[i][j])**2),y4[i][j],y1[i][j])
	print "\n"

# plt.clf();
# plt.imshow(log10(abs(x2-x1)),origin="bottom",extent=[-r,r,-r,r],aspect='auto')
# plt.colorbar()
# plt.clim(-15,0)



# figure()
# clf();imshow(x1);colorbar()
# figure()
# clf();imshow(x2);colorbar()












