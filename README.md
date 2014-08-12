SixTrackLib
===========

SixTrackLib is a tracking engine for particle tracking. It is implemented in C.

The whole code of library resides in kartikeya / sixtrack_lib / SixTrack / SixTrack_4518_cernlib_crlibm_gfortran_O4/SixTrackLib.c file. And the refactored fortran code resides in kartikeya / sixtrack_lib / SixTrack / SixTrack_4518_cernlib_crlibm_gfortran_O4/track.f file.

Steps to pull the repository: -
-----------------

1) mkdir SixTrackLib                                                           <br/>
2) git init                                                                    <br/>
2) git pull https://github.com/SixTrack/SixTrackLib.git                        <br/>

Steps to run the code: -
--------------------------

1) cd kartikeya / sixtrack_lib / SixTrack / SixTrack_4518_cernlib_crlibm_gfortran_O4  <br/>
2) make -f make_SixTrackLib                                                           <br/>
3) ./SixTrack_4518_cernlib_crlibm_gfortran_O4                                         <br/>
4) python read_fortbin.py                                                             <br/>

For any bug report or suggestion, please drop a mail at following addresses: -        <br/>
riccardo.de.maria@cern.ch                                                             <br/>
kartikeya107@gmail.com 
