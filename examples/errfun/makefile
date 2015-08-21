all: wwerf.so wwzsub.so wwzsubv.so


wwerf.so: erfr.f90
	f2py -m wwerf -c erfr.f90

wwzsub.so: wzsub.f90
	f2py -m wwzsub -c wzsub.f90

wwzsubv.so: wzsubv.f90
	f2py -m wwzsubv -c wzsubv.f90