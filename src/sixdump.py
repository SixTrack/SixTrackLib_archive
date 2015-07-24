import gzip

import numpy as np
import matplotlib.pyplot as pl

"""
nturn, i, ix, bez(ix), dcum(i),
xv(1,j)*1d-3, yv(1,j)*1d-3, xv(2,j)*1d-3, yv(2,j)*1d-3
ejfv(j)*1d-3 (ejv(j)-e0)*1d6
-1.0d-03*(sigmv(j)/clight)*(e0/e0f)
"""

class SixDump(object):
    pmass=938.272046e6
    clight=299792458
    @classmethod
    def open(cls,fn):
       out=[]
       if fn.endswith('.gz'):
           fh=gzip.open(fn)
       else:
           fh = file(fn)
       for l in fh:
        if len(l)>4:
          out.append(l.split())
       return cls(*zip(*out))
    def __init__(self,turn,elem,single,name,s,x,xp,y,yp,pc,de,tau,**args):
        apc=float(pc[0])*1e9
        ade=float(de[0])
        self.m0=self.pmass
        en=np.sqrt(apc**2+self.pmass**2)
        self.e0=en-ade
        self.p0c=np.sqrt(self.e0**2-self.m0**2)
        # structure
        self.elem=np.array(elem,dtype=int)
        self.turn=np.array(turn,dtype=int)
        d0=np.where(np.diff(self.elem)!=0)[0][0]+1
        d1=(np.where(np.diff(self.turn)!=0)[0][0]+1)/d0
        d2=len(self.turn)/d1/d0
        self.single=np.array(single,dtype=int)
        self.name=np.array(name,dtype=str)
        self.s =np.array(s ,dtype=float)
        self.x =np.array(x ,dtype=float)
        self.y =np.array(y ,dtype=float)
        self.tau=-np.array(tau,dtype=float)*self.clight
        opd=np.array(pc,dtype=float)*(1e9/self.p0c)
        self.delta=opd-1
        self.pt=np.array(de,dtype=float)/self.p0c
        self.px=np.array(xp,dtype=float)*opd
        self.py=np.array(yp,dtype=float)*opd
        for nn,vv in self.__dict__.items():
            if hasattr(vv,'__len__') and len(vv)==d0*d1*d2:
                setattr(self,nn,vv.reshape(d2,d1,d0))
    def get_particles(self,turn,elem=1,vl='m0 p0c s x px y py tau pt delta'):
       data={}
       for nn in vl.split():
           val=getattr(self,nn)
           if hasattr(val,'shape') and len(val.shape)==3:
               val=val[turn,elem,:].copy()
           data[nn]=val
       return data


