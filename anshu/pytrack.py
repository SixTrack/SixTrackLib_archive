#compiling with PIC: 		$ gcc -c -Wall -Werror -fpic track.c
#creating shared library: 	$ gcc -shared -o libtrack.so track.o
#or simply use the makefile instead of the above two commands (which ignores the warning)

import ctypes, math
from ctypes import *

ctypes.cdll.LoadLibrary("/home/aviral/Desktop/CERN code/Start/track.so") #or path of the shared object
libc = ctypes.CDLL("/home/aviral/Desktop/CERN code/Start/track.so") 	#or path of the shared object

#initializing argument variables
ThreeFloat = c_double * 3
ThreeInt = c_int * 1
TwoFloat = c_double * 2
argf = ThreeFloat(0,1,0)	#format of argf - [theta,cos(theta),sin(theta)]
argi = ThreeInt(0)		#format of argi - [ord]
coord = TwoFloat(0,1)		#format of coord - [x,y]

class Sequence(object):
  def __init__(self,coord,coordi):
    self.datai=[]
    self.dataf=[]
    self.coord=coord
    self.coordi=coordi
    self.lst=[]  
  def add_rot(self,angle):
    newid=len(self.datai)
    newfid=len(self.dataf)
    self.lst.extend([newid])
    self.datai.extend([newid,1,newfid,None])
    self.dataf.extend([angle,math.cos(angle),math.sin(angle)])
    return newid
  def add_kick(self,kv,order):
    newid=len(self.datai)
    newfid=len(self.dataf)
    self.lst.extend([newid])
    self.datai.extend([newid,2,newfid,None,order])
    self.dataf.extend([kv])
    return newid
  def add_counter(self,limit,count):
    newid=len(self.datai)
    newfid=len(self.dataf)
    self.lst.extend([newid])
    self.datai.extend([newid,3,newfid,None,limit,count])
    self.dataf.extend([])
    return newid
  def join(self):
    self.lst.extend([None])		
    i=1
    for index, value in enumerate(self.datai): 
      if value==None:
        if self.lst[i]==None:
          self.datai[index]=self.datai[0]
        else:
          self.datai[index]=self.lst[i]
          i = i+1
    return self
  def track(self,nturn,seq):
    self.join()
    c_nturn = ctypes.c_int(nturn)
    c_seq = ctypes.c_int(seq)
    arg_coordi=(ctypes.c_int *len(self.coordi))()
    arg_datai=(ctypes.c_int *len(self.datai))()
    arg_dataf=(ctypes.c_double *len(self.dataf))()
    arg_coord=(ctypes.c_double * len(self.coord))()
    for index, value in enumerate(self.datai):	
      arg_datai[index] = int(value) 
    for index, value in enumerate(self.dataf):
      arg_dataf[index] = float(value)
    for index, value in enumerate(self.coord):
      arg_coord[index] = float(value)
    for index, value in enumerate(self.coordi):
      arg_coordi[index] = int(value)
    val = libc.vec_map_loop(arg_dataf,arg_datai,arg_coord,arg_coordi)
    print val	  #for testing 
    return self

#adding features
seq=Sequence([0,0],[1,2])
rot=seq.add_rot(0.33*2*math.pi)
kick=seq.add_kick(0.02,2)
kick1=seq.add_kick(0.01,3)
count=seq.add_counter(10,0)
seq=seq.track(1,2)

#testing
var = libc.update_rot2d(argf,argi)
print var
var = libc.map_rot2d(argf,argi,coord)
print var
var = libc.map_kick2d(argf,argi,coord)
print var
var = libc.map_counter(argf,argi,coord)
print var
print seq.datai
print seq.dataf
