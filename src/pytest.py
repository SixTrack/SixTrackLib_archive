#compiling with PIC: 		$ gcc -c -Wall -Werror -fpic track.c
#creating shared library: 	$ gcc -shared -o libtrack.so track.o
#or simply use the makefile instead of the above two commands (which ignores the warning)

import sys, os
import ctypes, math
from random import randint
from ctypes import *

libfn=os.path.join(os.path.dirname(os.path.abspath(__file__)),'libtrack.so')
libc = ctypes.CDLL(libfn)

class Rot2d(object):
  _typeid=0
  def __init__(self,Element,**argsv):
    self._parameters={'angle':(0.0,1,0),'cx':(1.0,1,1),'sx':(0.0,1,2)}
    self.name = Element
    keys = sorted(argsv.keys())
    self._parameters[keys[0]]=(argsv[keys[0]],1,0)
    self._parameters['cx'] = (0,1,1)
    self._parameters['sx'] = (0,1,2)

class Kick2d(object):
  _typeid=1
  def __init__(self,Element,**argsv):
    self._parameters={'kv':(0.0,1,0),'order':(0,0,0)}
    self.name = Element
    keys = sorted(argsv.keys())
    self._parameters[keys[0]]=(argsv[keys[0]],1,0)
    self._parameters[keys[1]]=(argsv[keys[1]],0,0)

class Counter(object):
  _typeid=2
  def __init__(self,Element,**argsv):
    self._parameters={'count_max':(0,0,0),'count':(0,0,1)}
    self.name = Element
    keys = sorted(argsv.keys())
    self._parameters[keys[0]]=(argsv[keys[0]],0,0)
    self._parameters[keys[1]]=(argsv[keys[1]],0,1)

class Loop(object):
  _typeid=3
  def __init__(self,Element,**argsv):
    self.name = Element

class Monitor(object):
  _typeid=4
  def __init__(self,Element,**argsv):
    self.name = Element

class Simulation(object):
  elemi=[]
  elemf=[]
  parti=[]
  partf=[]
  npart=0

  def __init__(self):
    # self.elems={}
    self.lst={}

  def add_rot(self,label,angle):
    mapid=0
    elemid=len(self.elemi)
    mapst=len(self.elemf)
    i=0 #doubt
    j=1 #doubt
    self.elemi.extend([mapid,mapst,i,j])
    self.elemf.extend([angle,0,0])
    self.lst[label]=(elemid,mapid)
    Rot2d(label,angle=angle)

  def add_kick(self,label,kv,order):
    mapid=1
    elemid=len(self.elemi)
    mapst=len(self.elemf)
    i=0 #doubt
    j=1 #doubt
    self.elemi.extend([mapid,mapst,i,j,order])
    self.elemf.extend([kv])
    self.lst[label]=(elemid,mapid)
    Kick2d(label,kv=kv,order=order)

  def add_count(self,label,count_max):
    mapid=2
    elemid=len(self.elemi)
    mapst=-1
    count=1
    self.elemi.extend([mapid,mapst,count_max,count])
    self.elemf.extend([])
    self.lst[label]=(elemid,mapid)
    Counter(label,count_max=count_max,count=count)

  def add_loop(self,label,add_loop):
    mapid=3
    elemid=0
    mapst=-1
    elems=add_loop.split(' ')
    temp=[mapid,mapst,len(elems)]
    for elem in elems:
        self.lst[elem]=(self.lst[elem][0]+3+2*len(elems),self.lst[elem][1]) 
        temp.extend([self.lst[elem][0],self.lst[elem][1]])
    self.elemi=temp+self.elemi

  def add_monitor(self,label,nrec,skip,ndi,ndf):
    mapid=4
    elemid=len(self.elemi)
    mapst=len(self.elemf)
    self.elemi.extend([mapid,mapst,nrec,skip])
    i=0
    while i<nrec:
      self.elemi.extend([0,0])
      j=0
      while j<ndi:
        self.elemi.extend([0])
        self.elemf.extend([0.0])
        j=j+1
      i=i+1
    self.lst[label]=(elemid,mapid)
    Monitor(label,nrec=nrec,skip=skip)

  def add_elem(self,name,label,*args):
    if(name=='rot2d'):
        self.add_rot(label,*args)
    elif(name=='kick2d'):
        self.add_kick(label,*args)
    elif(name=='counter'):
        self.add_count(label,*args)
    elif(name=='loop'):
        self.add_loop(label,*args)
    elif(name=='monitor'):
        self.add_monitor(label,*args)

  def add_part(self,coordf,coordi):
    self.npart=self.npart+1
    ndf=len(coordf)
    ndi=len(coordi)
    stf=len(self.partf)
    sti=len(self.parti)
    if(len(self.parti)):
        self.parti[0]=self.npart
        self.parti[1]=ndf
        self.parti[2]=ndi
        self.parti[3]=stf
        self.parti[4]=sti
    else:
        sti=0
        if(len(coordi)):
            sti=sti+5
    self.parti.extend([self.npart,ndf,ndi,stf,sti])
    self.parti.extend(coordi)
    self.partf.extend(coordf)

  # def search(self,label):
  #   tag=label.split('.')  
  #   if self.elems[tag[0]][0]._parameters.has_key(tag[1])==True:
  #       main = self.elems[tag[0]][1]
  #       choice = self.elems[tag[0]][0]._parameters[tag[1]][1]
  #       offset = self.elems[tag[0]][0]._parameters[tag[1]][2]
  #   if choice==0:
  #     ret = 2*(main+offset+4)
  #   if choice==1:
  #     ret = 2*(self.datai[main+2]+offset)+1
  #   return 3*ret+2, self.elems[tag[0]][0]._typeid 

  def simulate(self):
    arg_elemi=(ctypes.c_int *len(self.elemi))()
    arg_elemf=(ctypes.c_double *len(self.elemf))()
    arg_parti=(ctypes.c_int *len(self.parti))()
    arg_partf=(ctypes.c_double *len(self.partf))()
    for index, value in enumerate(self.elemi):
      arg_elemi[index] = int(value) 
    for index, value in enumerate(self.elemf):
      arg_elemf[index] = float(value)
    for index, value in enumerate(self.parti):
      arg_parti[index] = int(value)
    for index, value in enumerate(self.partf):
      arg_partf[index] = float(value)
    arg_elemid=0
    arg_partid=0
    arg_npart=1

    libc.loop_init(arg_elemi, arg_elemf, arg_elemid)
    var=libc.loop_map(arg_elemi, arg_elemf, arg_elemid, arg_parti, arg_partf, arg_partid, arg_npart)
    libc.print_var(arg_elemi, arg_elemf, arg_parti, arg_partf, 5)
    return self

sim=Simulation()
sim.add_elem('rot2d','r1',math.pi/2)
sim.add_elem('rot2d','r2',-math.pi/4)
sim.add_elem('kick2d','k1',0.3,2)
sim.add_elem('monitor','m1',2,1,0,2)
sim.add_elem('counter','c1',2)
sim.add_elem('loop','l1','r1 r2 k1 m1 c1')
sim.add_part([12,2],[])
# sim.add_part([.2,.2],[2])
# sim.add_part([.4,.4],[2])

print sim.elemi
print sim.elemf
print sim.parti
print sim.partf
sim.simulate()


# elemiInt = c_int*28
# elemfFloat = c_double*7
# partiInt = c_int*5
# partfFloat = c_double*2

# elemi = elemiInt( 3,-1,4,11,0,15,0,19,1,24,2,
#                   0,0,0,1,
#                   0,3,0,1,
#                   1,6,0,1,2,
#                   2,-1,2,1)
# elemf = elemfFloat( math.pi/2,0,0,
#                    -math.pi/4,0,0,
#                     0.3)
# elemid = 0
# parti = partiInt(1,2,0,0,0)
# partf = partfFloat(12,2)
# partid = 0
# npart = 1

# libc.print_var(elemi, elemf, parti, partf)
# libc.loop_init(elemi, elemf, elemid)
# var = libc.loop_map(elemi, elemf, elemid, parti, partf, partid, npart)
# libc.print_var(elemi, elemf, parti, partf)
# print var
