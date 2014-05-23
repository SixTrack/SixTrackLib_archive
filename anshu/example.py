
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


class Sequence(object):
   def __init__(self,coord):
     self.datai=[]
     self.dataf=[]
     self.coord=coord
   def add_rot(self,angle):
     newid=len(self.datai) 
     newfid=len(self.dataf)
     self.datai.extend([newid,1,newfid,None])
     self.dataf.append([angle,cos(angle),sin(angle)])
     return newid
   def add_kick(self,kv,ord):
     newid=len(self.datai)
     newfid=len(self.dataf)
     self.datai.extend([newid,2,newfid,None,ord])
     self.dataf.append([kv])
     return newid
   def join(self,lst):
     for e1,e2 in zip(lst[:-1],lst[1:]):
       self.datai[e1+3]=e2
     self.datai[e2+3]=lst[0]
     return self
   def track(self,lst):
     libc.vec_map_loop(array(self.datai),array(self.dataf),self.coord)
     return seq

seq=Sequence()
rot=seq.add_rot(0.33*2*pi)
kick=seq.add_kick(0.02,2)
count=seq.add_counter(100)
seq=seq.join().track()

