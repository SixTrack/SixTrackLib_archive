SixTrackLib
===========

SixTrackLib is a tracking engine for particle tracking. It is implemented in C.

The `src` folder contains implementations of various Sixtrack Maps in C and Python. 

The `examples` folder has the Benchmarking results (in `examples/benchmark files`) for the C Maps and error functions against Sixtrack and Python and codes for generating the same. The benchmarking has been completed for the following maps:

``Drift`` 
``Drift_Exact``
``Multipole``
``Align``
``Block``
and for ``errf()`` and ``wzsub()`` error functions.

The `anshu` folder contains code for Differential Algebra and RPN calculator in C and RPN parser in Python.

The `kartikeya` folder holds the Sixtrack Legacy code, the refactored Sixtrack code, an initial version of the C Library and some map test results.

Steps to clone the repository: -
-----------------

1) git clone https://github.com/SixTrack/SixTrackLib.git                           <br/>   

Steps to run the refactored C code: -
--------------------------

1) change directory to `src` using cd src                                              <br/>
2) edit the SRCS macro in the makefile and run make                                   <br/>
3) edit `track.py` python API to enter appropriate Input for the maps provided        <br/> 
3) run make test                                                                      <br/>

Steps to run the previous version of code: -
--------------------------

1) cd kartikeya / sixtrack_lib / SixTrack / SixTrack_4518_cernlib_crlibm_gfortran_O4  <br/>
2) make -f make_SixTrackLib                                                           <br/>
3) ./SixTrack_4518_cernlib_crlibm_gfortran_O4                                         <br/>
4) python read_fortbin.py                                                             <br/>

For any bug report or suggestion, please drop a mail at following addresses: -        <br/>
riccardo.de.maria@cern.ch                                                             <br/>
kartikeya107@gmail.com                                                                <br/>
aviral.2815@gmail.com
