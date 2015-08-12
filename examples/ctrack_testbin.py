from numpy import *
import matplotlib.pyplot as pl
from sixtracklib.ctrack import *

from sixtracklib.pysixtrack import *
from sixtracklib.sixdump import SixDump
from sixtracklib.sixinput import SixTrackInput
from sixtracklib.sixbin   import SixBin

s=SixTrackInput('med_80_mo_3_s1_4-6_30')

out,rest=s.expand_struct()
convert={'drift':DriftExact, 'mult':Multipole, 'cav': Cavity}
out=[ (name,ccc,convert[el.__class__.__name__](*el)) for name,ccc,el in out]

# d=SixDump.open('med_80_mo_3_s1_4-6_30/dump.dat.gz')

# p=Bunch(**d.get_particles(0,0))

partiInt = ctypes.c_int*5
partfFloat = ctypes.c_double*14

parti = partiInt(1,9,0,5,5)
elemid = 0
partid = 0
npart = 1

# def pprint(p0,p):
#   res=0
#   out=[]
#   for nn in 'x px y py delta'.split():
#       ss=getattr(p0,nn)
#       pp=getattr(p,nn)
#       err=sqrt(sum((ss-pp)**2))
#       if abs(ss)>0:
#         err/=abs(ss)
#       out.append((nn,err,ss,pp))
#       #print "%-6s %23.16e %23.16e %23.16e"%(nn,err,ss,pp)
#       res+=err
#   return res,out

b=SixBin('med_80_mo_3_s1_4-6_30')
p=Bunch(**b.get_particle(1,0))
res={}
res[0]=p
print p
# err={}
# for  iii,(name,ccc,el) in enumerate(out):
#   el.track(p)
#   pnew=p.copy()
#   p=Bunch(**b.get_particle(1,iii+1))
#   #print iii,p.s,el
#   res,rrr=pprint(p,pnew)
#   err[res]=(iii,p.s,el,rrr)


# for kk in sorted(err.keys(),reverse=True)[:10]:
#     iii,s,el,val=err[kk]
#     print iii,s,el
#     for nn,re,ss,pp in val:
#       print "%-6s %23.16e %23.16e %23.16e"%(nn,re,ss,pp)

for name,ccc,el in out:
    partf = partfFloat(p.p0c, p.beta0, p.gamma0, p.m0, p.e0, p.x, p.px, p.y, p.py, p.tau, p.pt, p.delta, p.s, p.chi)
    print el, "\n\nC Map:"
    if isinstance(el,DriftExact):
        elemiInt = ctypes.c_int*2
        elemfFloat = ctypes.c_double*1
        elemi = elemiInt(6,0)
        elemf = elemfFloat(el.l)
        var = libtrack.drift_exact_map(elemi, elemf, elemid, parti, partf, partid, npart)

    if isinstance(el,Multipole):
        elemiInt = ctypes.c_int*4
        elemi = elemiInt(7,0,len(el.knl),len(el.ksl))
        tempElemf = []; tempElemf.extend(el.knl); tempElemf.extend(el.ksl); tempElemf.extend([el.hxl, el.hyl, el.l, el.rel])
        elemf = (ctypes.c_double *len(tempElemf))()
        for index, value in enumerate(tempElemf):
      		elemf[index] = float(value)
        var = libtrack.multipole_map(elemi, elemf, elemid, parti, partf, partid, npart)

    if isinstance(el,Cavity):
        elemiInt = ctypes.c_int*2
        elemfFloat = ctypes.c_double*4
        elemi = elemiInt(8,0)
        elemf = elemfFloat(el.vn, el.f, el.lag, el.scav)
        var = libtrack.cavity_map(elemi, elemf, elemid, parti, partf, partid, npart)

    el.track(p)
    print "Python Map:"
    for nn in 's x px y py tau delta pt'.split():
        pp=getattr(p,nn)[0]
        print "%-6s %23.16e"%(nn,pp)
    print "\n"