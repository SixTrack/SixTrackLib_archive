from sixtracklib.pysixtrack import *
from sixtracklib.sixdump import SixDump
from sixtracklib.sixinput import SixTrackInput
from sixtracklib.sixbin   import SixBin

# from pyoptics import *
from numpy import *

#t=optics.open('med_80_mo_3_s1_4-6_30/twiss.tfs')
#err=optics.open('med_80_mo_3_s1_4-6_30/errors.tfs')
s=SixTrackInput('med_80_mo_3_s1_4-6_30')


out,rest=s.expand_struct()
convert={'drift':Drift, 'mult':Multipole, 'cav': Cavity}
out=[ (name,ccc,convert[el.__class__.__name__](*el)) for name,ccc,el in out]

def pprint(p0,p):
  res=0
  out=[]
  for nn in 'x px y py delta'.split():
      ss=getattr(p0,nn)
      pp=getattr(p,nn)
      err=sqrt(sum((ss-pp)**2))
      if abs(ss)>0:
        err/=abs(ss)
      out.append((nn,err,ss,pp))
      #print "%-6s %23.16e %23.16e %23.16e"%(nn,err,ss,pp)
      res+=err
  return res,out


b=SixBin('med_80_mo_3_s1_4-6_30')
p=Bunch(**b.get_particle(1,0))
err={}
for  iii,(name,ccc,el) in enumerate(out):
  el.track(p)
  pnew=p.copy()
  p=Bunch(**b.get_particle(1,iii+1))
  #print iii,p.s,el
  res,rrr=pprint(p,pnew)
  err[res]=(iii,p.s,el,rrr)


for kk in sorted(err.keys(),reverse=True)[:10]:
    iii,s,el,val=err[kk]
    print iii,s,el
    for nn,re,ss,pp in val:
      print "%-6s %23.16e %23.16e %23.16e"%(nn,re,ss,pp)









