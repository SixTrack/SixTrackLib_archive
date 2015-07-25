from sixtracklib.pysixtrack import *
from sixtracklib.sixdump import SixDump
from sixtracklib.sixinput import SixTrackInput

# from pyoptics import *
from numpy import *

#t=optics.open('med_80_mo_3_s1_4-6_30/twiss.tfs')
#err=optics.open('med_80_mo_3_s1_4-6_30/errors.tfs')
s=SixTrackInput('med_80_mo_3_s1_4-6_30')

out,rest=s.expand_struct()
convert={'drift':DriftExact, 'mult':Multipole, 'cav': Cavity}
out=[ (name,ccc,convert[el.__class__.__name__](*el)) for name,ccc,el in out]

#out[:4]
#rest[:4]
#madname='mqwa.a4r3.b1..1'
#s.compare_madmult('q_c6t_1',0,err,'mqwa.a4r3.b1..1')
#[ (nnn,el) for nnn,el in out if type(el)==cav]
#[ (nnn,el) for nnn,el in out if getattr(el,'knl',[0])[0]!=0]

d=SixDump.open('med_80_mo_3_s1_4-6_30/dump.dat.gz')


p=Bunch(**d.get_particles(0,0))
res={}
res[0]=p
for iii,(name,ccc,el) in enumerate(out):
   el.track(p)
   res[iii+1]=(name,el,p.copy())

for idx in range(0,d.elem.shape[1]):
  iii=d.elem[0,idx,0]
  name,el,p=res[iii]
  print d.name[0,idx,0],ccc,name
  print el
  berr=0
  for nn in 's x px y py tau delta'.split():
     ss=getattr(d,nn)[0,idx,0]
     pp=getattr(p,nn)[0]
     err=sqrt(sum((ss-pp)**2))/ss
     print "%-6s %23.16e %23.16e %23.16e"%(nn,err,ss,pp)
     if nn not in ['s','tau']:
       berr+=err