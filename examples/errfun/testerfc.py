import mpmath as mp
import matplotlib.pyplot as plt
from numpy import *
from sixtracklib.ctrack import *
import scipy

from wwerf import ccperrfr as wf90
# wf90=vectorize(wf90)
from wwzsub import wzsub as wz
from wwzsub import wzset as wset
# from wwzsubv import wzset as wzv
# wf=vectorize(wf)

# from mywwerf import wwerf as wpy

from scipy.special import erfc, wofz
mp.dps = 32

# print(mp.quad(lambda x: mp.exp(-x**2), [-mp.inf, mp.inf]) ** 2)

# def wofzmp(x,y):
#     z=x+1j*y
#     w=mp.exp(-z**2) * mp.erfc(z * -1j)
#     return w.real,w.imag

# wofzmp=vectorize(wofzmp)

# def wsci(x,y):
#     z=x+1j*y
#     w=wofz(z)
#     return w.real,w.imag

# wsci=vectorize(wsci)

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

# x1,y1=array(wsci(x,y),dtype=float)
# x2,y2=wf90(x,y)
# # x3,y3=wf(x,y)
# x4,y4=array(wofzmp(x,y),dtype=float)
# print shape(x1)
napx=1
for i in range(0,31):	
	for j in range(0,31):
		xxreal=x[i][j]
		yyimag=y[i][j]

		#RUN FORTRAN wzsub
		wset()
		wxreal,wyimag=wz(xxreal,yyimag)

		#RUN FORTRAN wzsubv
		# wset()
		# wxreal,wyimag=wzv(napx,xxreal,yyimag)

		#RUN FORTRAN errf
		# wxreal,wyimag=wf90(xxreal,yyimag)
		
		# RUN PYTHON wofz/errf
		# z=np.complex(xxreal,yyimag)
		# k=scipy.special.wofz(z)

		# wxreal=k.real
		# wyimag=k.imag

		# wxreal=x2[i][j]
		# wyimag=y2[i][j]

		#RUN C errf/wzsub/wzsubv
		elemFloat = ctypes.c_double*4
		inp = elemFloat(xxreal,yyimag,wxreal,wyimag)

		var = libtrack.benchmark_errf(inp)

		# print "%-6s %23.16e %23.16e %23.16e"%("PYreal",sqrt((wxreal-k.real)**2),wxreal,k.real)
		# print "%-6s %23.16e %23.16e %23.16e\n"%("PYimag",sqrt((wyimag-k.imag)**2),wyimag,k.imag)

		# print "%-6s %23.16e %23.16e"%("real",wxreal,xxreal)
		# print "%-6s %23.16e %23.16e\n"%("imag",wyimag,yyimag)
	print "\n"

# plt.clf();
# plt.imshow(log10(abs(x2-x1)),origin="bottom",extent=[-r,r,-r,r],aspect='auto')
# plt.colorbar()
# plt.clim(-15,0)

# figure()
# clf();imshow(x1);colorbar()
# figure()
# clf();imshow(x2);colorbar()




# import numpy as np
# from sixtracklib.ctrack import *
# import scipy
# from scipy import special

# r=15
# xx=10**np.linspace(-r,r,31)
# yy=10**np.linspace(-r,r,31)
# x,y=np.meshgrid(xx,yy)
# k = [0 for i in range(0,31*31)]
# for i in range(0,31):
# 	for j in range(0,31):
# 		# k[j+31*i]=np.complex(x[i][j],y[i][j])

# 		real=x[i][j]
# 		imag=y[i][j]

# 		z=np.complex(real,imag)
# 		k=scipy.special.wofz(z)

# 		# print z.real, z.imag, k.real, k.imag

# 		elemFloat = ctypes.c_double*4
# 		inp = elemFloat(z.real,z.imag,k.real,k.imag)
# 		# vy = elemFloat(z.imag)
# 		# wx = elemFloat(k.real)
# 		# wy = elemFloat(k.imag)

# 		# inp=[vx,vy,wx,wy]
# 		# elemf = (ctypes.c_double *len(inp))()
# 		# for index, value in enumerate(inp):
# 		    # num[index] = float(value)
# 		# print vx,vy,wx,wy

# 		var = libtrack.benchmark_errf(inp)
# print var







