import numpy as np
import matplotlib.pyplot as pl

from sixtracklib.ctrack import Rot2D, Kick2D, Counter, Monitor, Loop, Elements, Particles


print Rot2D.make_c_header()
print Kick2D.make_c_header()
print Counter.make_c_header()
print Monitor.make_c_header()
print Loop.make_c_header()

npart=33
nturns=2000

coord=np.zeros((npart,2))
coord[:,0]=np.linspace(0,.5,npart)
part=Particles.from_arrays(coord)

el=Elements()
el.add('monitor','m1' ,nturns+1,1,part)
el.add('rot2d'  ,'r1' ,0.31123,0,1)
el.add('kick2d' ,'k1' ,1.1,2,0,1)
el.add('counter','c1' ,nturns)
el.add('loop'  ,'seq',el._elem_ids)

el.pprint()

#el.r1.track(part)
#el.k1.track(part)
el.seq.update()
el.seq.track(part)


constf,coordf=el.m1.splitf()

pl.clf()
for pp in range(part.npart):
    pl.plot(coordf[:,pp,0],coordf[:,pp,1],'.')

pl.xlim(-2,2)
pl.ylim(-2,2)
pl.show()
