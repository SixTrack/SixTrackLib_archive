track.o: track.c
	gcc -c -Wall -Werror -fpic track.c -O3

track.so: track.o
	gcc -shared  $<  -o $@
