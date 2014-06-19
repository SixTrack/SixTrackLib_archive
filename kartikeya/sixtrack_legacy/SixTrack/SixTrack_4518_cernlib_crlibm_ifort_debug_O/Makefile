SHELL = /bin/sh

FC = ifort
FCF =  -O -mia32 -fp-model source -fp-model strict -fp-model no-except
FCL = -static -m32
FCLD = -m32
FCLMAP = -Wl,--print-map -static -m32
CRLIBM = crlibm/crlibm.a
CERNLIB = 
gfortran_lib = 
BOINC = 
NAGLIBC = 
BEAMGAS = 
SIXTRACK = SixTrack_4518_cernlib_crlibm_ifort_debug_O

%.o: %.f
	$(FC) -c $(FCF) $<

%.o: %.f90
	$(FC) -c $(FCF) $<

all: SixTrack_4518_cernlib_crlibm_ifort_debug_O

dafor: dafor.o
	$(FC) $(FCLD) -o dafor dafor.o

astuce: astuce.o
	$(FC) $(FCLD) -o astuce astuce.o $(NAGLIBC)

myboinc.o: myboinc.f
	$(FC) -c $(FCF) myboinc.f

SixTrack_4518_cernlib_crlibm_ifort_debug_O: $(MYHDF5LIB) track.o sixve.o sixvefox.o dabnews.o lielib.o $(BEAMGAS) $(BOINC) $(CRLIBM)
	$(FC) $(FCLMAP) -o SixTrack_4518_cernlib_crlibm_ifort_debug_O track.o sixve.o sixvefox.o dabnews.o lielib.o $(BEAMGAS) \
	$(BOINC) $(CERNLIB) $(CRLIBM) $(gfortran_lib) > sixtrack.map 2>&1

: sixda.o sixsc.o sixscfox.o dabnew.o lielib.o $(CRLIBM)
	$(FC) $(FCLMAP) -o  sixda.o sixsc.o sixscfox.o dabnew.o lielib.o \
	$(NAGLIB) $(NAGLIBC) $(CRLIBM) $(gfortran_lib) > sixtrack_da.map 2>&1

clean: 
	rm -f *.ast *.s *.c *.o SixTrack_4518_cernlib_crlibm_ifort_debug_O 
