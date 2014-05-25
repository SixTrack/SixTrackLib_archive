
"""
datai=
//id type f_data next_elem other_args
   0 1    0      4               //rot
   4 2    3      9         2     //kick  ord=2
   9 3    -1     0         100  0  //limit=100 count=0 (no floating data)

dataf=
  2.07 -0.4817... 0.87630  //  angle= 0.33*2*pi
  0.03                     //  kv=0.03
"""
import math

class Sequence(object):
	def __init__(self,coord):
		self.datai=[]
		self.dataf=[]
		self.coord=coord
	def add_rot(self,angle):
		newid=len(self.datai)
		newfid=len(self.dataf)
		self.datai.extend([newid,1,newfid,None])
		self.datai.append([])
		self.dataf.append([angle,math.cos(angle),math.sin(angle)])
		return newid
	def add_kick(self,kv,order):
		newid=len(self.datai)
		newfid=len(self.dataf)
		self.datai.extend([newid,2,newfid,None])
		self.datai.append([order])
		self.dataf.append([kv])
		return newid
	def add_counter(self,limit,count):
		newid=len(self.datai)
		newfid=len(self.dataf)
		self.datai.extend([newid,3,newfid,None])
		self.datai.append([limit,count])
		self.dataf.append([])
	def join(self):
		length = len(self.datai)
		e1=0
		while e1<=(length-10): 
			self.datai[e1+3]=self.datai[e1+5]
			e1=e1+5
		self.datai[e1+3]=self.datai[0]
		return self
	def track(self):
		libc.vec_map_loop(array(self.datai),array(self.dataf),self.coord)
		return seq

seq=Sequence([0,0])
rot=seq.add_rot(0.33*2*math.pi)
kick=seq.add_kick(0.02,2)
count=seq.add_counter(100,2)
seq=seq.join().track()
