import mpmath as mp
import matplotlib.pyplot as plt
from numpy import *
from sixtracklib.ctrack import *
import scipy

from wwerf import ccperrfr as wf90
from wwzsub import wzsub as wz
from wwzsub import wzset as wset

from scipy.special import erfc, wofz

r=15
xx=10**linspace(-r,r,31)
yy=10**linspace(-r,r,31)
x,y=meshgrid(xx,yy)

napx=1
for i in range(0,31):	
	for j in range(0,31):
		xxreal=x[i][j]
		yyimag=y[i][j]

		#RUN FORTRAN wzsub
		wset()
		wxreal,wyimag=wz(xxreal,yyimag)

		## RUN FORTRAN wzsubv
		# wset()
		# wxreal,wyimag=wzv(napx,xxreal,yyimag)

		## RUN FORTRAN errf
		# wxreal,wyimag=wf90(xxreal,yyimag)
		
		## RUN PYTHON wofz/errf
		# z=np.complex(xxreal,yyimag)
		# k=scipy.special.wofz(z)

		# wxreal=k.real
		# wyimag=k.imag

		#RUN C errf/wzsub/wzsubv
		elemFloat = ctypes.c_double*4
		inp = elemFloat(xxreal,yyimag,wxreal,wyimag)

		var = libtrack.benchmark_errf(inp)

		## PRINT PYTHON BENCHMARKS
		# print "%-6s %23.16e %23.16e %23.16e"%("PYreal",sqrt((wxreal-k.real)**2),wxreal,k.real)
		# print "%-6s %23.16e %23.16e %23.16e\n"%("PYimag",sqrt((wyimag-k.imag)**2),wyimag,k.imag)
	print "\n"


# # REFERENCES
# #https://github.com/PyCOMPLETE/PyHEADTAIL/master/spacecharge/spacecharge.py

# #http://www.bigdft.org/devel-doc/d0/dfa/wofz_8f90_source.html
# #http://www.bigdft.org/devel-doc/d0/dfa/wofz_8f90.html
# #http://dl.acm.org/citation.cfm?id=77629
# # latest
# #www.ccsenet.org/journal/index.php/jmr/article/viewFile/41877/24151 
# # http://ab-initio.mit.edu/wiki/index.php/Faddeeva_Package
# # arxiv.org/pdf/1407.0748 In root with source code