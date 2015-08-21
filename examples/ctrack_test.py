from numpy import *
import matplotlib.pyplot as pl
from sixtracklib.ctrack import *

from sixtracklib.pysixtrack import *
from sixtracklib.sixdump import SixDump
from sixtracklib.sixinput import SixTrackInput
from sixtracklib.sixbin   import SixBin

exampledir='med_80_mo_3_s1_4-6_30'
# exampledir='med_80_bb_2_s1_4-6_30'
# exampledir='med_80_mo_3_s1_0sigma'

s=SixTrackInput(exampledir)
convert={'drift':Drift, 'mult':Multipole, 'cav': Cavity,
         'align':Align,'block':Block}
out,rest=s.expand_struct(convert=convert)

b=SixBin(exampledir)

p=Bunch(**b.get_particle(1,0))

partiInt = ctypes.c_int*5
partfFloat = ctypes.c_double*14

parti = partiInt(1,9,0,5,5)
elemid = 0
partid = 0
npart = 1

for iii,(name,ccc,el) in enumerate(out[:21]):
    print el
    partf = partfFloat(p.p0c, p.beta0, p.gamma0, p.m0, p.e0, p.x, p.px, p.y, p.py, p.tau, p.pt, p.delta, p.s, p.chi)
    if isinstance(el,Drift):
        elemiInt = ctypes.c_int*2
        elemfFloat = ctypes.c_double*1
        elemi = elemiInt(5,0)
        elemf = elemfFloat(el.l)
        var = libtrack.drift_map(elemi, elemf, elemid, parti, partf, partid, npart)

    elif isinstance(el,Multipole):
        elemiInt = ctypes.c_int*4
        elemi = elemiInt(7,0,len(el.knl),len(el.ksl))
        tempElemf = []; tempElemf.extend(el.knl); tempElemf.extend(el.ksl); tempElemf.extend([el.hxl, el.hyl, el.l, el.rel])
        elemf = (ctypes.c_double *len(tempElemf))()
        for index, value in enumerate(tempElemf):
            elemf[index] = float(value)
        var = libtrack.multipole_map(elemi, elemf, elemid, parti, partf, partid, npart)

    elif isinstance(el,Cavity):
        elemiInt = ctypes.c_int*2
        elemfFloat = ctypes.c_double*4
        elemi = elemiInt(8,0)
        elemf = elemfFloat(el.vn, el.f, el.lag, el.scav)
        var = libtrack.cavity_map(elemi, elemf, elemid, parti, partf, partid, npart)

    elif isinstance(el,Align):
        elemiInt = ctypes.c_int*2
        elemfFloat = ctypes.c_double*3
        elemi = elemiInt(9,0)
        elemf = elemfFloat(el.dx, el.dy, el.tilt)
        var = libtrack.align_map(elemi, elemf, elemid, parti, partf, partid, npart)

    elif isinstance(el,Block):
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
    el.track(p)
    p=Bunch(**b.get_particle(1,iii+1))
    pprint(p)
    print "\n"