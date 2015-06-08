#compiling with PIC: 		$ gcc -c -Wall -Werror -fpic track.c
#creating shared library: 	$ gcc -shared -o libtrack.so track.o
#or simply use the makefile instead of the above two commands (which ignores the warning)

import sys
import ctypes, math
from random import randint
from ctypes import *

ctypes.cdll.LoadLibrary("/home/aviral/Desktop/CERN code/NextRound/test/libtrack.so") #or path of the shared object
libc = ctypes.CDLL("/home/aviral/Desktop/CERN code/NextRound/test/libtrack.so") 	#or path of the shared object

elemiInt = c_int*28
elemfFloat = c_double*7
partiInt = c_int*5
partfFloat = c_double*2

elemi = elemiInt( 3,-1,4,11,0,15,0,19,1,24,2,
                  0,0,0,1,
                  0,3,0,1,
                  1,6,0,1,2,
                  2,-1,2,1)
elemf = elemfFloat( math.pi/2,0,0,
                   -math.pi/4,0,0,
                    0.3)
elemid = 0
parti = partiInt(1,2,0,0,0)
partf = partfFloat(12,2)
partid = 0
npart = 1

libc.print_var(elemi, elemf, parti, partf)
libc.loop_init(elemi, elemf, elemid)
var = libc.loop_map(elemi, elemf, elemid, parti, partf, partid, npart)
libc.print_var(elemi, elemf, parti, partf)
print var