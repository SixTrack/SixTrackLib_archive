#compiling with PIC: 		$ gcc -c -Wall -Werror -fpic track.c
#creating shared library: 	$ gcc -shared -o libtrack.so track.o
#or simply use the makefile instead of the above two commands (which ignores the warning)

import sys
import ctypes, math
from random import randint
from ctypes import *

ctypes.cdll.LoadLibrary("/home/aviral/Desktop/Projects/SixTrackLib/src/libtrack.so") #or path of the shared object
libc = ctypes.CDLL("/home/aviral/Desktop/Projects/SixTrackLib/src/libtrack.so") 	#or path of the shared object

elemiInt = c_int*6
elemfFloat = c_double*9
partiInt = c_int*5
partfFloat = c_double*2

elemi = elemiInt(0, 0, 4, 0, 8)
elemf = elemfFloat(math.pi/2,0,0,-math.pi/2,0,0, math.pi/3,0,0)
elemid = 0
parti = partiInt(1,2,0,0,0)
partf = partfFloat(1,1)
partid = 0
npart = 1

var = libc.rot2d_init(elemi, elemf, elemid)
print var
libc.print_var_rot(elemi, elemf, parti, partf)
var = libc.rot2d_map(elemi, elemf, elemid, parti, partf, partid, npart)
libc.print_var_rot(elemi, elemf, parti, partf)
print var

elemiInt = c_int*9
elemfFloat = c_double*3

elemi = elemiInt(0, 0, 2, 0, 4, 4, 0, 8, 6)
elemf = elemfFloat(0.03, 0.01, 0.2)
elemid = 0
parti = partiInt(1,2,0,0,0)
partf = partfFloat(1,1)
partid = 0
npart = 1

var = libc.kick2d_init(elemi, elemf, elemid)
print var
libc.print_var_kick(elemi, elemf, parti, partf)
var = libc.kick2d_map(elemi, elemf, elemid, parti, partf, partid, npart)
libc.print_var_kick(elemi, elemf, parti, partf)
print var
