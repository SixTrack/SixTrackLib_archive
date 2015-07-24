import sys, os
import ctypes
import numpy as np
import matplotlib.pyplot as pl

libfn=os.path.join(os.path.dirname(os.path.abspath(__file__)),'libtrack.so')
libtrack = ctypes.CDLL(libfn)
c_double_p=ctypes.POINTER(ctypes.c_double)
c_int_p=ctypes.POINTER(ctypes.c_int)

def mk_int_buffer(ll):
    return (ctypes.c_int*ll)()
def mk_float_buffer(ll):
    return (ctypes.c_double*ll)()

def myadd(a,b):
    if str(a).isdigit() and str(b).isdigit():
        return str(int(a)+int(b))
    else:
        return "%s+%s"%(a,b)

class ParamElem(object):
    __slots__=('valtype','index','size')
    def __init__(self, valtype,index,size):
        self.valtype=valtype
        self.index=index
        self.size=size

class Param(object):
    """
      if valtype is None, valtype is taken from default value
      if size is None, size is taken from the default value
    """
    __slots__=('name','default','size','valtype','desc')
    def __init__(self,name,default,desc=None,size=None,valtype=None):
        self.name=name
        self.desc=desc
        self.size=size
        if valtype is None:
          if hasattr(default,'__len__'):
            self.valtype=type(default[0])
          else:
            self.valtype=type(default)
        if size is None:
          if hasattr(default,'__len__'):
            size=len(value)
          else:
            size=1
        self.size=size
        self.default=default
    def validate(self,nargs):
      if self.name in nargs:
          value=nargs[self.name]
      else:
          value=self.default
      size=self.size
      if type(size) is str:
        size=eval(size,{},nargs)
      if size>0:
        if hasattr(value,'__len__'):
            if len(value)!=size:
               raise ValueError
            else:
               value=[self.valtype(vvv) for vvv in value]
        else:
           value=[self.valtype(value)]*size
      else:
        value=[self.valtype(value)]
      return value,size


class Element(object):
    @classmethod
    def make_c_header(cls):
      i_index="0"
      f_index="0"
      out=['#define %s_TYPE %d'%(cls._label,cls._typeid)]
      for par in cls._params:
          if par.valtype is float:
              out.append("#define %s_float_%s %s"%(cls._label,par.name,f_index))
              f_index=myadd(f_index,par.size)
          elif par.valtype is int:
              out.append("#define %s_int_%s %s"%(cls._label,par.name,i_index))
              i_index=myadd(i_index,par.size)
      return '\n'.join(out)
    def __init__(self,storage,elemid,floatid,*args,**nargs):
        self._storage=storage
        self._elemid=elemid
        self._floatid=floatid
        self._data={}
        i_values,f_values=self.validate(*args,**nargs)
        storage._add_memory(len(i_values),len(f_values))
        storage._add_values(elemid,floatid,i_values,f_values)
        self._trackfun=getattr(libtrack,self._label+'_map')
        nonefun=lambda a,b,c: None
        self._updatefun=getattr(libtrack,self._label+'_update',nonefun)
        self.update()
    def validate(self,*args,**nargs):
        f_values=[]
        i_values=[self._typeid,self._floatid]
        i_index=2+self._elemid
        f_index=self._floatid
        for par,val in zip(self._params,args):
            nargs[par.name]=val
        for par in self._params:
            val,size=par.validate(nargs)
            if par.valtype is float:
                self._data[par.name]=ParamElem(par.valtype,f_index,size)
                f_values.extend(val)
                f_index+=size
            elif par.valtype is int:
                self._data[par.name]=ParamElem(par.valtype,i_index,size)
                i_values.extend(val)
                i_index+=size
        return i_values,f_values
    def __getattr__(self,k):
        par=self._data[k]
        offset=par.index
        size=par.size
        if par.valtype is int:
            value=self._storage._get_int_value(offset,size)
        elif par.valtype is float:
            value=self._storage._get_float_value(offset,size)
        if size==1:
            value=value[0]
        return value
    def __setattr__(self,k,v):
        try:
          par=object.__getatttribute__(self,'_data')[k]
          offset=par.index
          size=par.size
          if par.valtype is int:
              self._storage._set_int_value(offset,v)
          elif par.valtype is float:
              self._storage._set_float_value(offset,v)
        except AttributeError:
          object.__setattr__(self,k,v)
    def __dir__(self):
        return [par.name for par in self._params]
    def pprint(self):
        for par in self._params:
          if par.valtype is int:
              ttt='i'
          elif par.valtype is float:
              ttt='f'
          val=str(getattr(self,par.name))
          offset=self._data[par.name].index
          if len(val)>53:
              val=val[:25]+'...'+val[-25:]
          print "%s:%-10s(%2d)->%s"%(ttt,par.name,offset,val)
    def track(self,part,partid=0,partn=None):
        elemid=self._elemid
        elemi=self._storage._elemi
        elemf=self._storage._elemf
        parti=part._elemi
        partf=part._elemf
        partid=partid
        if partn is None:
            partn=part.npart
        self._trackfun(elemi,elemf,elemid,
                parti,partf,partid,partn)
    def update(self):
        elemid=self._elemid
        elemi=self._storage._elemi
        elemf=self._storage._elemf
        self._updatefun(elemi,elemf,elemid)



class StorageProp(object):
    def __init__(self,offset):
        self.offset=offset
    def __get__(self,obj,cls=None):
        return obj._elemi[self.offset]
    def __set__(self,obj,value):
        obj._elemi[self.offset]=value

class Elements(object):
    _last_i=StorageProp(0)
    _last_f=StorageProp(1)
    _elem_num=StorageProp(2)
    def __init__(self):
        self._elemf=mk_float_buffer(256)
        self._elemi=mk_int_buffer(256)
        self._etypes=dict([(c._label,c) for c in Element.__subclasses__()])
        self._last_i=3
        self._last_f=0
        self._elem_num=0
        self._elem_ids=[]
        self._elem_names=[]
    def add(self,etype,name,*args,**nargs):
        cls=self._etypes[etype]
        elemid=self._last_i
        floatid=self._last_f
        print args,nargs
        elem=cls(self,elemid,floatid,*args,**nargs)
        setattr(self,name,elem)
        self._elem_ids.append(elemid)
        self._elem_names.append(name)
        self._elem_num+=1
        return elemid
    def _add_memory(self,imem,fmem):
        self._last_i+=imem
        self._last_f+=fmem
        max_size_i=len(self._elemi)
        max_size_f=len(self._elemf)
        if self._last_i>max_size_i:
            newbuffer=mk_int_buffer(int(self._last_i*1.5))
            newbuffer[:max_size_i]=self._elemi
            self._elemi=newbuffer
        if self._last_f>max_size_f:
            newbuffer=mk_float_buffer(int(self._last_f*1.5))
            newbuffer[:max_size_f]=self._elemf
            self._elemf=newbuffer
    def _add_values(self,sti,stf,i_values,f_values):
        for iii,ival in enumerate(i_values):
           self._elemi[sti+iii]=ival
        for iii,fval in enumerate(f_values):
           self._elemf[stf+iii]=fval
    def _get_int_value(self,offset,size):
        return self._elemi[offset:offset+size]
    def _get_float_value(self,offset,size):
        return self._elemf[offset:offset+size]
    def _set_int_value(self,offset,value):
        self._elemi[offset:offset+size]=value
    def _set_float_value(self,offset,value):
        self._elemf[offset:offset+size]=value
    def pprint(self):
        for nn in self._elem_names:
          print nn
          getattr(self,nn).pprint()
    def __repr__(self):
        return "<Elements n:%d i:%d f:%d>"%(
                len(self._elem_ids),self._last_i,self._last_f)

class Index(Element):
    _label='index'
    _typeid=-1
    _params=[ Param('last_i'  ,3,''),
              Param('last_f'  ,0,''),
              Param('first_i' ,3,''),
              Param('elem_num',0,'')]


class Rot2D(Element):
    _label='rot2d'
    _typeid=0
    _params=[ Param('angle',1.0,'rotation angle in unit of [2 Pi]'),
              Param('i'    ,0,'x-like coordinate index'),
              Param('j'    ,1,'y-like coordinate index'),
              Param('cx'   ,1.0,'cos(angle)'),
              Param('sx'   ,0.0,'sin(angle)'),
            ]

class Kick2D(Element):
    _label='kick2d'
    _typeid=1
    _params=[ Param('k',1.0,'coefficient of the kick'),
              Param('o',2,'order of the kick'),
              Param('i',1,'x-like coordinate index'),
              Param('j',0,'y-like coordinate index'),
            ]

class Counter(Element):
    _label='counter'
    _typeid=2
    _params=[ Param('count_max',1,'maximum count'),
              Param('count'    ,0,'actual count'),
            ]

class Monitor(Element):
    _label='monitor'
    _typeid=4
    _params=[ Param('nrec' ,0,''),
              Param('skip' ,0,''),
              Param('isize',0,''),
              Param('fsize',0,''),
              Param('count',0,''),
              Param('last' ,0,''),
              Param('index',0,'','nrec'),
              Param('datai',0,'','isize*nrec'),
              Param('dataf',0.0,'','fsize*nrec'),
            ]
    def __init__(self,storage,elemid,floatid,nrec,skip,part):
        isize,fsize=part.get_size()
        Element.__init__(self,storage,elemid,floatid,nrec,skip,isize,fsize)
        self.part=part
    def splitf(self):
        nrec=self.nrec
        fsize=self.fsize
        npart=self.part.npart
        stf=self.part.stf
        ndf=self.part.ndf
        out=np.array(self.dataf).reshape(nrec,fsize)
        constf=[]
        coordf=[]
        for dataf in out:
            constf.append(dataf[:stf])
            coordf.append(dataf[stf:])
        constf=np.array(constf)
        coordf=np.array(coordf).reshape(nrec,npart,ndf)
        return constf,coordf



class Loop(Element):
    _label='loop'
    _typeid=3
    _params=[ Param('nelem',0,''),
              Param('elems' ,0,'','nelem'),
            ]
    def __init__(self,storage,elemid,floatid,elems):
        nelem=len(elems)
        Element.__init__(self,storage,elemid,floatid,nelem,elems)

class Drift(Element):
    _label='drift'
    _typeid=5
    _params=[ Param('L',1.0,'physical length of block'),
            ]

class Drift_Exact(Element):
    _label='drift_exact'
    _typeid=6
    _params=[ Param('L',1.0,'physical length of block'),
            ]

class Multipole(Element):
    _label='multipole'
    _typeid=7
    _params=[ Param('Knlen',0,'length of Kn'),
              Param('Kslen',0,'length of Ks'),
              Param('Hxl',1.0,''),
              Param('Hxl',1.0,''),
              Param('L',1.0,'physical length of block'),
              Param('Rel',1.0,''),
            ]

class Cavity(Element):
    _label='cavity'
    _typeid=8
    _params=[ Param('Vn',0,'Voltage of the Cavity'),
              Param('Freq',0,'Frequency of Cavity'),
              Param('Lag',1.0,'Lag Phase Of Cavity'),
              Param('S0',1.0,''),
            ]

class Particles(object):
    npart=StorageProp(0)
    ndf=StorageProp(1)
    ndi=StorageProp(2)
    stf=StorageProp(3)
    sti=StorageProp(4)
    @classmethod
    def from_arrays(cls,coordf,coordi=[],constf=[],consti=[]):
        stf=len(constf)
        sti=5+len(consti)
        npart,ndf=coordf.shape
        coordf=coordf.flatten()
        ndi=0
        if len(coordi)>0:
          nparti,ndi=coordi.shape
          if npart!=nparti:
            raise ValueError
          coordi=coordi.flatten()
        elemi=mk_int_buffer(sti+ndi*npart)
        elemf=mk_float_buffer(stf+ndf*npart)
        elemi[:5]=[npart,ndf,ndi,stf,sti]
        elemi[5:sti]=consti
        elemi[sti:]=coordi
        elemf[:stf]=constf
        elemf[stf:]=coordf
        return cls(elemi,elemf)
    @property
    def coordf(obj):
        data=np.array(obj._elemf[obj.stf:],dtype=float)
        return data.reshape(obj.npart,obj.ndf)
    @property
    def coordi(obj):
        data=np.array(obj._elemi[obj.sti:],dtype=np.int32)
        if len(data)>0:
          data=data.reshape(obj.npart,obj.ndi)
        return data
    @property
    def consti(obj):
        data=np.array(obj._elemi[5:obj.sti],dtype=np.int32)
        return data
    @property
    def constf(obj):
        data=np.array(obj._elemf[5:obj.stf],dtype=float)
        return data
    def __init__(self,elemi,elemf):
      self._elemi=elemi
      self._elemf=elemf
    def get_size(self):
      isize=self.sti+self.ndi*self.npart
      fsize=self.stf+self.ndf*self.npart
      return isize,fsize