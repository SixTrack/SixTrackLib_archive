###README:

This folder contains source code for various maps, programs for reading Sixtrack Input and Output files, python maps and a file to call the C maps with a user-friendly python API. 
The C maps in this folder can be categorised as follows:

1. Generic Maps: loop.c, counter.c, monitor.c
2. Sixtrack Maps: drift.c, drift_exact.c, multipole.c, multipole_hor.c, multipole_ver.c, beambeam.c, normal_pole.c, skew_pole.c, dipole.c, cavity.c, rf_cavity.c,  
3. Nd Maps: kick2d.c, rot2d.c
4. Assist Maps: align.c, block.c, extra.c, results.c

The python files and their brief description is as follows:

1. pysixtrack.py: contains pythons maps and a class to instantiate particle coordinates
2. sixinput.py: contains class to read the Sixtrack input
3. sixbin.py: contains class to read Sixtrack output
4. ctrack.py: generates Elements that can be passed as an input to C maps
5. track.py: contains python API to call the C maps using shared library

Create the shared library using:
`make`
