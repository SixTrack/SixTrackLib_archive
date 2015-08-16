import numpy as np
from sixtracklib.ctrack import *
import scipy
from scipy import special

r=15
xx=10**np.linspace(-r,r,31)
yy=10**np.linspace(-r,r,31)
x,y=np.meshgrid(xx,yy)
k = [0 for i in range(0,31*31)]
for i in range(0,31):
	for j in range(0,31):
		# k[j+31*i]=np.complex(x[i][j],y[i][j])

		real=x[i][j]
		imag=y[i][j]

		z=np.complex(real,imag)
		k=scipy.special.wofz(z)

		# print z.real, z.imag, k.real, k.imag

		elemFloat = ctypes.c_double*4
		inp = elemFloat(z.real,z.imag,k.real,k.imag)
		# vy = elemFloat(z.imag)
		# wx = elemFloat(k.real)
		# wy = elemFloat(k.imag)

		# inp=[vx,vy,wx,wy]
		# elemf = (ctypes.c_double *len(inp))()
		# for index, value in enumerate(inp):
		    # num[index] = float(value)
		# print vx,vy,wx,wy

		var = libtrack.benchmark_errf(inp)
print var