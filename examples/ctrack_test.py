from numpy import *
import matplotlib.pyplot as pl
from sixtracklib.ctrack import *

from sixtracklib.pysixtrack import *
from sixtracklib.sixdump import SixDump
from sixtracklib.sixinput import SixTrackInput
from sixtracklib.sixbin   import SixBin

# s=SixTrackInput('med_80_mo_3_s1_4-6_30')

# out,rest=s.expand_struct()
# convert={'drift':DriftExact, 'mult':Multipole, 'cav': Cavity, 'block': Block}
# out=[ (name,ccc,convert[el.__class__.__name__](*el)) for name,ccc,el in out]

exampledir='med_80_mo_3_s1_4-6_30'
# exampledir='med_80_bb_2_s1_4-6_30'
# exampledir='med_80_mo_3_s1_0sigma'

s=SixTrackInput(exampledir)
convert={'drift':Drift, 'mult':Multipole, 'cav': Cavity,
         'align':Align,'block':Block}
out,rest=s.expand_struct(convert=convert)
print out
b=SixBin('med_80_mo_3_s1_4-6_30')

p=Bunch(**b.get_particle(1,0))
res={}
res[0]=p
# print p.m0
partiInt = ctypes.c_int*5
partfFloat = ctypes.c_double*14

parti = partiInt(1,9,0,5,5)
elemid = 0
partid = 0
npart = 1

for iii,(name,ccc,el) in enumerate(out[:21]):
    print el
    partf = partfFloat(p.p0c, p.beta0, p.gamma0, p.m0, p.e0, p.x, p.px, p.y, p.py, p.tau, p.pt, p.delta, p.s, p.chi)
    # print el, "\n\nC Map:"
    if isinstance(el,Drift):
        elemiInt = ctypes.c_int*2
        elemfFloat = ctypes.c_double*1
        elemi = elemiInt(5,0)
        elemf = elemfFloat(el.l)
        var = libtrack.drift_map(elemi, elemf, elemid, parti, partf, partid, npart)

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

    if isinstance(el,Align):
        elemiInt = ctypes.c_int*2
        elemfFloat = ctypes.c_double*3
        elemi = elemiInt(9,0)
        elemf = elemfFloat(el.dx, el.dy, el.tilt)
        var = libtrack.align_map(elemi, elemf, elemid, parti, partf, partid, npart)

    if isinstance(el,Block):
        tempIds=[10,0,len(el.elems)]
        tempElemi=[]; tempElemf=[]
        for elem in el.elems:
            if isinstance(elem,Align):
                tempIds.extend([3+len(el.elems)+len(tempElemi)])
                tempElemi.extend([9,len(tempElemf)]); tempElemf.extend([elem.dx, elem.dy, elem.tilt])
            if isinstance(elem,Multipole):
                tempIds.extend([3+len(el.elems)+len(tempElemi)])
                tempElemi.extend([7,len(tempElemf),len(elem.knl),len(elem.ksl)]);
                tempElemf.extend(elem.knl); tempElemf.extend(elem.ksl); tempElemf.extend([elem.hxl, elem.hyl, elem.l, elem.rel])
        tempElemi = tempIds + tempElemi
        elemi = (ctypes.c_int *len(tempElemi))()
        elemf = (ctypes.c_double *len(tempElemf))()
        for index, value in enumerate(tempElemi):
            elemi[index] = int(value)
        for index, value in enumerate(tempElemf):
            elemf[index] = float(value)
        var = libtrack.block_map(elemi, elemf, elemid, parti, partf, partid, npart)
        # print intcount, floatcount
        # print tempElemi
        # print tempElemf

        # elemiInt = ctypes.c_int*(3+2*len(el.elems))
        # # elemfFloat = ctypes.c_double*3
        # tempElemf = [10,0,len(el.elems)]
        # for elem in el.elems:
        #     if isinstance(elem,Align):
        #         tempElemf.extend()
        #     if isinstance(elem,Multipole):
        # # elemi = elemiInt(10,0,len(el.elems))
        # # elemf = elemfFloat()
        # elemf = []
        # var = libtrack.align_map(elemi, elemf, elemid, parti, partf, partid, npart)
        # print "Block Called"

    # print "Python Map:", iii
    el.track(p)
    # pnew=p.copy()
    p=Bunch(**b.get_particle(1,iii+1))
    pprint(p)
    # res,rrr=pprint(p,pnew)
    # for nn in 's x px y py tau delta pt'.split():
    #     pp=getattr(p,nn)
    #     print "%-6s %23.16e"%(nn,pp)
    print "\n"
    # el.track(p)
    # print "Python Map:"
    # for nn in 's x px y py tau delta pt'.split():
    #     pp=getattr(p,nn)[0]
    #     print "%-6s %23.16e"%(nn,pp)
    # print "\n"

# b=SixBin(exampledir)
# p=Bunch(**b.get_particle(1,0))
# err={}
# bench=[]
# for  iii,(name,ccc,el) in enumerate(out):
#   el.track(p)
#   pnew=p.copy()
#   p=Bunch(**b.get_particle(1,iii+1))
#   print iii,p.s,el
#   res,rrr=pprint(p,pnew)
#   err[res]=(iii,name,el,rrr)
#   bench.append(err[res])



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