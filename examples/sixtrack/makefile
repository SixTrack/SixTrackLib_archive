OBJ=dabnews.o  lielib.o  sixvefox.o  sixve.o  track.o beamgas.o

%.o: %.f
	gfortran -m32  -frecord-marker=4 -g -fno-second-underscore -funroll-loops -O3 -c -o $@ $<

sixtrack: $(OBJ) crlibm
	gfortran -m32 -o sixtrack $(OBJ) crlibm/crlibm.a -static

.PHONY: crlibm

crlibm:
	$(MAKE) -C crlibm
