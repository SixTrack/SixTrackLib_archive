from sixtracklib.ctrack import *
from collections import namedtuple
from copy import deepcopy

import numpy as np

class Bunch(object):
  clight=299792458
  pi=3.141592653589793238
  echarge=1.602176565e-19
  emass=0.510998928e6
  pmass=938.272046e6
  epsilon0=8.854187817e-12
  mu0=4e-7*pi
  eradius=echarge**2/(4*pi*epsilon0*emass*clight**2)
  pradius=echarge**2/(4*pi*epsilon0*pmass*clight**2)
  anumber=6.02214129e23
  kboltz=1.3806488e-23
  def _g1(self,m0,p0c,e0):
      beta0=p0c/e0;     gamma0=e0/m0
      return m0,beta0,gamma0,p0c,e0
  def _g2(self,m0,beta0,gamma0):
      e0=m0*gamma0;     p0c=e0*beta0
      return m0,beta0,gamma0,p0c,e0
  def _f1(self,m0,p0c):
      sqrt=self._m.sqrt
      e0=sqrt(p0c**2+m0**2)
      return self._g1(m0,p0c,e0)
  def _f2(self,m0,e0):
      sqrt=self._m.sqrt
      p0c=sqrt(e0**2-m0**2)
      return self._g1(m0,p0c,e0)
  def _f3(self,m0,beta0):
      sqrt=self._m.sqrt
      gamma0=1/sqrt(1-beta0**2)
      return self._g2(m0,beta0,gamma0)
  def _f4(self,m0,gamma0):
      sqrt=self._m.sqrt
      beta0=sqrt(1-1/gamma0**2)
      return self._g2(m0,beta0,gamma0)
  def copy(self):
      p=Bunch()
      for k,v in self.__dict__.items():
          if type(v) in [np.ndarray,dict]:
              v=v.copy()
          p.__dict__[k]=v
      return p
  def __init__(self,s=0.,x=0.,px=0.,y=0.,py=0.,tau=0.,pt=None,delta=None,
               q0=1,m0=pmass,beta0=None,gamma0=None,p0c=None,e0=None,
               mratio=1.0,qratio=1.0,chi=None,
               mathlib=np,**args):
    self._m=mathlib
    self.s=s
    self.x=x; self.px=px
    self.y=y; self.py=py
    self._m0=m0
    self._p0c=p0c
    self._e0=e0
    self._gamma0=gamma0
    self._beta0=beta0
    self.tau=tau
    self._pt=pt
    self._delta=delta
    self._chi=chi
    self._qratio=qratio
    self._mratio=mratio
    if p0c is not None:
       self._update_ref(*self._f1(m0,p0c))
    elif e0 is not None:
       self._update_ref(*self._f2(m0,e0))
    elif beta0 is not None:
       self._update_ref(*self._f3(m0,beta0))
    elif gamma0 is not None:
       self._update_ref(*self._f4(m0,beta0))
    if qratio is not None:
       self._chi=self._qratio/self._mratio
    elif chi is not None:
       self._qratio=self._chi*self._mratio
    if delta is not None:
        self.delta=delta
    elif pt is not None:
        self.pt=pt
  # fully depent quantities
  Px=property(lambda p: p.px*p.p0c*p.mratio)
  Py=property(lambda p: p.py*p.p0c*p.mratio)
  E =property(lambda p: (p.pt*p.p0c+p.e0)*p.mratio)
  Pc=property(lambda p: (p.delta*p.p0c+p.p0c)*p.mratio)
  m =property(lambda p:  p.m0*p.mratio)
  beta =property(lambda p:  (1+p.delta)/(1/p.beta0+p.pt))
  # interdepent quantities
  pt=property(lambda self: self._pt)
  @pt.setter
  def pt(self,pt):
    sqrt=self._m.sqrt
    self._pt=pt
    self._delta=sqrt(pt**2+2*pt/self.beta0+1)-1
  delta=property(lambda self: self._delta)
  @delta.setter
  def delta(self,delta):
    sqrt=self._m.sqrt
    self._delta=delta
    self._pt=sqrt((1+self.delta)**2+1/(self.beta0*self.gamma0)**2)-1/self.beta0
  m0=property(lambda self: self._m0)
  @m0.setter
  def m0(self,m0):
    new=self._f1(m0,self.p0c)
    self._update_ref(*new)
    self._update_particles(*new)
  beta0=property(lambda self: self._beta0)
  @beta0.setter
  def beta0(self,beta0):
    new=self._f3(self.m0,beta0)
    self._update_ref(*new)
    self._update_particles(*new)
  gamma0=property(lambda self: self._gamma0)
  @gamma0.setter
  def gamma0(self,gamma0):
    new=self._f4(self.m0,gamma0)
    self._update_ref(*new)
    self._update_particles(*new)
  p0c=property(lambda self: self._p0c)
  @p0c.setter
  def p0c(self,p0c):
    new=self._f1(self.m0,p0c)
    self._update_ref(*new)
    self._update_particles(*new)
  e0=property(lambda self: self._e0)
  @e0.setter
  def e0(self,e0):
    new=self._f2(self.m0,e0)
    self._update_ref(*new)
    self._update_particles(*new)
  mratio=property(lambda self: self._mratio)
  @mratio.setter
  def mratio(self,mratio):
    Px,Py,E,Pc=self.Px,self.Py,self.E,self.Pc
    self._pt=E/(mratio*e0)-1
    self._delta=E/(delta*e0)-1
    self.px=Px/(p0c*mratio)
    self.py=Py/(p0c*mratio)
    self._chi=self._qratio/mratio
    self._mratio=mratio
  qratio=property(lambda self: self._qratio)
  @qratio.setter
  def qratio(self,qratio):
    self._chi=qratio/self._mratio
    self._qratio=qratio
  chi=property(lambda self: self._chi)
  @chi.setter
  def chi(self,chi):
    self._qratio=self._chi*self._mratio
    self._chi=chi
  def _update_ref(self,m0,beta0,gamma0,p0c,e0):
    self._m0=m0
    self._beta0=beta0
    self._gamma0=gamma0
    self._p0c=p0c
    self._e0=e0
  def _update_particles(self,m0,beta0,gamma0,p0c,e0):
    Px,Py,E,Pc,m=self.Px,self.Py,self.E,self.Pc,self.m
    mratio=m/m0
    self._mratio=mratio
    self._chi=self._qratio/mratio
    self._pt=E/(mratio*e0)-1
    self._delta=E/(delta*e0)-1
    self.px=Px/(p0c*mratio)
    self.py=Py/(p0c*mratio)
  def __repr__(self):
    out=[]
    for nn in 'm0 p0c e0 beta0 gamma0'.split():
      out.append('%-7s = %s'%(nn,getattr(self,nn)))
    for nn in 's x px y py tau pt delta'.split():
      out.append('%-7s = %s'%(nn,getattr(self,nn)))
    for nn in 'mratio qratio chi'.split():
      out.append('%-7s = %s'%(nn,getattr(self,nn)))
    return '\n'.join(out)


def ctaylor(x,y,kn,ks):
  dpx=kn[-1]
  dpy=ks[-1]
  nn=range(1,len(kn)+1)
  for nn,kkn,kks in zip(nn,kn,ks)[-2::-1]:
    dpx=kkn+(dpx*x-dpy*y)/float(nn)
    dpy=kks+(dpx*y+dpy*x)/float(nn)
  return dpx,dpy

def pprint(p):
  res=0
  out=[]
  tempPart=[]
  for nn in 'p0c beta0 gamma0 m0 e0 x px y py tau pt delta s chi'.split():
      # ss=getattr(p0,nn)
      pp=getattr(p,nn)
      tempPart.extend([pp])
      # err=sqrt(sum((ss-pp)**2))
      #if abs(ss)>0 and nn!='tau':
      #  err/=abs(ss)
      # out.append((nn,err,ss,pp))
      # print "%-6s %23.16e %23.16e %23.16e"%(nn,err,ss,pp)
      # print "%-6s %23.16e"%(nn,pp)
      # res+=err
  # print tempPart
  partf = (ctypes.c_double *len(tempPart))()
  for index, value in enumerate(tempPart):
            partf[index] = float(value)
  var = libtrack.print_comp(partf)
  return res,out

class Drift(namedtuple('Drift',['l'])):
    def track(self,p):
        l=self.l
        opdi=1/(1+p.delta)
        lbeta0i=l/p.beta0
        lbetai=(lbeta0i+p.pt*l)*opdi
        # print "p lbeta0i: %23.17e\np pt: %23.16e\np lbetai: %23.16e\np opdi: %23.16e\np l: %23.16e"%(lbeta0i,p.pt,lbetai,opdi,l)
        # print "p p.pt*l: %23.17e\np lbeta0i+p.pt*l: %23.17e\n"%(p.pt*l,lbeta0i+p.pt*l)
        xp=p.px*opdi; yp=p.py*opdi
        p.x+=xp*l ;  p.y+=yp*l
        # print ""%(p.tau)
        p.tau+=lbeta0i-lbetai*(1+(xp**2+yp**2)/2)
        # print "p lbetai: %23.16e\np taua: %23.16e"%(lbetai, lbetai*(1+(xp**2+yp**2)/2))
        p.s+=l
        # pprint(p,p)

class DriftExact(namedtuple('Drift',['l'])):
    def track(self,p):
        sqrt=p._m.sqrt
        l=self.l
        px=p.px;py=p.py;beta0=p.beta0;delta=p.delta;pt=p.pt
        pzi=l/sqrt((1+delta)**2-px**2-py**2)
        print "py pzi:", pzi
        bzi=(1/beta0+pt)*pzi
        print "py bzi:", bzi
        xp=px*pzi; yp=py*pzi
        p.x+=xp ;  p.y+=yp
        p.tau+=l/beta0-bzi
        p.s+=l
        # pprint(p,p)

class Multipole(namedtuple('Multipole','knl ksl hxl hyl l rel'.split())):
    def track(self,p):
        # print "py multipole"
        kn=self.knl; ks=self.ksl
        # if relative order is defined 0->obsolute k
        if self.rel>0:
          fact=kn[p.rel]
          for i in range(p.rel,len(kn)):
             kn*=p.knl[p.rel]
             ks*=p.ksl[p.rel]
        x=p.x;y=p.y; chi=p.chi ;
        # multipole kick
        dpx=kn[-1] ;  dpy=ks[-1]
        nn=range(1,len(kn)+1)
        for nn,kkn,kks in zip(nn,kn,ks)[-2::-1]:
          zre=(dpx*x-dpy*y)/float(nn)
          zim=(dpx*y+dpy*x)/float(nn)
          dpx=kkn+zre
          dpy=kks+zim
        dpx=-chi*dpx
        dpy=chi*dpy
        # curvature effect kick
        l=self.l
        if l!=0:
          betai=(1/p.beta0+p.pt)/(1+p.delta)
          b1l=chi*kn[0]; a1l=chi*ks[0]
          hxl=self.hxl ;  hyl=self.hyl
          hxx=hxl/l*x; hyy=hyl/l*y; delta=p.delta
          dpx+=hxl + hxl*delta - b1l*hxx
          dpy-=hyl + hyl*delta - a1l*hyy
          p.tau-=chi*(hxx-hyy)*l*betai
        p.px+=dpx ;  p.py+=dpy
        # pprint(p,p)


class Cavity(namedtuple('Cavity','vn f lag scav'.split())):
    def track(self,p):
      sin=p._m.sin
      pi=p._m.pi
      k=2*pi*self.f/p.clight
      phase=self.lag*pi/180-k*p.tau
      if self.scav>=0:
        # for cogging phi is the phase when s=scav
        phase+=k*(p.s-self.scav)/p.beta0
      p.pt+=p.chi*self.vn*sin(phase)
      # pprint(p,p)


class Align(namedtuple('Align','dx dy tilt'.split())):
    def track(self,p):
      sin=p._m.sin
      cos=p._m.cos
      pi=p._m.pi
      an=-self.tilt*pi/180
      cx=cos(an); sx=sin(an)
      # print "p cx: %23.16e\np sx: %23.16e\n"%(cx,sx)
      xn=-self.dx; yn=-self.dy
      # print "p xn: %23.16e\np yn: %23.16e\n"%(xn,yn)
      xn+= cx*p.x+sx*p.y
      yn+=-sx*p.x+cx*p.y
      # print "p p.px: %23.16e\np p.py: %23.16e\n"%(p.px,p.py)
      p.x=xn;p.y=yn;
      pxn= cx*p.px+sx*p.py
      # print "p cx*p.px: %23.16e\np sx*p.py: %23.16e\n"%(cx*p.px,sx*p.py)
      pyn=-sx*p.px+cx*p.py
      # print "p pxn: %23.16e\np pyn: %23.16e\n"%(pxn,pyn)
      p.px=pxn;p.py=pyn;
      # pprint(p,p)


class Block(namedtuple('Block','elems'.split())):
    def track(self,p):
        for el in self.elems:
            el.track(p)


