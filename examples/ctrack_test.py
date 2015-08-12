from numpy import *
import matplotlib.pyplot as pl
from sixtracklib.ctrack import *

from sixtracklib.pysixtrack import *
from sixtracklib.sixdump import SixDump
from sixtracklib.sixinput import SixTrackInput

s=SixTrackInput('med_80_mo_3_s1_4-6_30')

out,rest=s.expand_struct()
convert={'drift':DriftExact, 'mult':Multipole, 'cav': Cavity}
out=[ (name,ccc,convert[el.__class__.__name__](*el)) for name,ccc,el in out]

d=SixDump.open('med_80_mo_3_s1_4-6_30/dump.dat.gz')

p=Bunch(**d.get_particles(0,0))
res={}
res[0]=p

partiInt = ctypes.c_int*5
partfFloat = ctypes.c_double*14

parti = partiInt(1,9,0,5,5)
elemid = 0
partid = 0
npart = 1

for name,ccc,el in out:
    partf = partfFloat(p.p0c, p.beta0, p.gamma0, p.m0, p.e0, p.x[0], p.px[0], p.y[0], p.py[0], p.tau[0], p.pt[0], p.delta[0], p.s[0], p.chi)
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


# print Rot2D.make_c_header()
# print Kick2D.make_c_header()
# print Counter.make_c_header()
# print Monitor.make_c_header()
# print Loop.make_c_header()
# print Drift.make_c_header()
# print Drift_Exact.make_c_header()
# print Multipole.make_c_header()
# print Cavity.make_c_header()

# npart=33
# nturns=2000

# coord=np.zeros((npart,2))
# coord[:,0]=np.linspace(0,.5,npart)
# part=Particles.from_arrays(coord)

# el=Elements()
# el.add('monitor','m1' ,nturns+1,1,part)
# el.add('drift_exact','de1' ,0.3)
# el.add('multipole'  ,'m1' ,2,2,0.0,0.0,0.0,0.0,0,0,0)
# # el.add('cavity' ,'cav1' ,0.0,200415682.47964293,0,-1)
# el.add('counter','c1' ,nturns)
# el.add('loop'  ,'seq',el._elem_ids)

# el.pprint()

# #el.r1.track(part)
# #el.k1.track(part)
# el.seq.update()
# el.seq.track(part)


# constf,coordf=el.m1.splitf()

# pl.clf()
# for pp in range(part.npart):
#     pl.plot(coordf[:,pp,0],coordf[:,pp,1],'.')

# pl.xlim(-2,2)
# pl.ylim(-2,2)
# pl.show()