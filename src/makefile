CC= gcc
CFLAGS= -fpic
LDFLAGS= -shared
SRCS = kick2d.c rot2d.c counter.c loop.c results.c monitor.c drift_exact.c rf_cavity.c dipole.c normal_pole.c skew_pole.c multipole_hor.c multipole_ver.c beambeam.c
OBJECTS= $(SRCS:.c=.o)
TARGET_LIB= libtrack.so
INCLUDES= hmacro.h

.PHONY: all clean
all: $(TARGET_LIB)

test: $(TARGET_LIB)
	python track.py

$(TARGET_LIB): $(OBJECTS)
	$(CC) $(LDFLAGS) -o libtrack.so loop.o

.c.o: $(INCLUDES)
	$(CC) -O3 -c $(CFLAGS) $<  

clean:
	rm $(OBJECTS) $(TARGET_LIB)