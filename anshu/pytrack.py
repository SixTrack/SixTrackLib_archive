#compiling with PIC: 		$ gcc -c -Wall -Werror -fpic track.c
#creating shared library: 	$ gcc -shared -o libtrack.so track.o
#or simply use the makefile instead of the above two commands (which ignores the warning)

import ctypes
from ctypes import *

ctypes.cdll.LoadLibrary("/home/aviral/Desktop/Sixtrack/Start/track.so") #or path of the shared object
libc = ctypes.CDLL("/home/aviral/Desktop/Sixtrack/Start/track.so") 	#or path of the shared object

#initializing argument variables
ThreeFloat = c_double * 3
ThreeInt = c_int * 1
TwoFloat = c_double * 2
argf = ThreeFloat(0,1,0)	#format of argf - [theta,cos(theta),sin(theta)]
argi = ThreeInt(0)		#format of argi - [ord]
coord = TwoFloat(0,1)		#format of coord - [x,y]

#to check if functions return properly
var = libc.update_rot2d(argf,argi)
print var
var = libc.map_rot2d(argf,argi,coord)
print var
var = libc.map_kick2d(argf,argi,coord)
print var
var = libc.map_counter(argf,argi,coord)
print var
