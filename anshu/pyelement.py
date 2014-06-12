class Rot2d:
  _typeid=1
  _parameters={'angle':(0.0,0),'cx':(1.0,1),'sx':(0.0,2)}

class Kick2d:
  _typeid=2
  _parameters={'kv':(0.0,0),'order':(0,1)}

class Counter:
  _typeid=3
  _parameter={'limit':(0,0),'count':(0,1)}

class Element(object):
  lst=[]
  def __init__(self,datai,dataf,elem_type,**argsv):
#    cls=self.__class__
    self.elem_id=len(datai)
    self.idx_float=len(dataf)
    self.elem_type=elem_type
    self.lst.extend([self.elem_id])
    datai.extend([self.elem_id,self.elem_type,self.idx_float,None])
    if elem_type==1:
      lst=[(keyidx,key,value) for key,(value,keyidx) in Rot2d._parameters.items()]
    if elem_type==2:
      lst=[(keyidx,key,value) for key,(value,keyidx) in Kick2d._parameters.items()]
    if elem_type==3:
      lst=[(keyidx,key,value) for key,(value,keyidx) in Counter._parameters.items()]
    print sorted(lst)
    for (keyidx,key,value) in sorted(lst):
      valtype=type(value)
      if key in argsv:
        value=valtype(argsv[key])
        print 'arg',value
      if valtype==float:
        dataf.append(value)
        print 'daf',value
      elif valtype==int:
        datai.append(value)
        print 'dai',value
    self.datai=datai
    self.dataf=dataf
    print self.lst
    self.join()
    print self.datai
    print self.dataf
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

class TrackData(object):
  def __init__(self,coord):
    self.coord=coord
    self.datai=[]
    self.dataf=[]
    self.elems={}
  def add_elem(self,name,eltype,**argsv):
    el=eltype(**argsv)
    keys = sorted(argsv.keys())
    for kw in keys:
        print kw, ":", argsv[kw]
    self.elems[name]=el

"""datai = [0, 1, 0, 4, 4, 2, 3, 9, 2, 9, 2, 4, 14, 3, 14, 3, 5, 0, 10, 1]
dataf = [2.0734511513692637, -0.48175367410171543, 0.8763066800438635, 0.02, 0.01]"""
coord = [1,1]
coordi = [1,3]
datai=[]
dataf=[]
Element(datai,dataf,2,kv=0.32,order=2)              
Element(datai,dataf,1,angle=0.21,cx=0.68,sx=0.19)
