#!/bin/sh
gcc -c -Wall -Werror -fpic rot2d.c
gcc -c -Wall -Werror -fpic kick2d.c
gcc -c -Wall -Werror -fpic counter.c
gcc -c -Wall -Werror -fpic loop.c
gcc -c -Wall -Werror -fpic results.c
gcc -shared -o libtrack.so rot2d.o kick2d.o loop.o counter.o results.o
python pytest.py
