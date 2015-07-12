CC= gcc
CFLAGS= -fpic
LDFLAGS= -shared
SRCS = kick2d.c rot2d.c counter.c loop.c results.c monitor.c drift_exact.c rf_cavity.c horizontal_dipole.c vertical_dipole.c normal_pole.c skew_pole.c multipole_hor.c multipole_ver.c
OBJECTS= $(SRCS:.c=.o)
TARGET_LIB= libtrack.so
INCLUDES= hmacro.h

.PHONY: all clean
all: $(TARGET_LIB)

test: $(TARGET_LIB)
	python pytest.py

$(TARGET_LIB): $(OBJECTS)
	$(CC) $(LDFLAGS) -o libtrack.so $(OBJECTS)

.c.o: $(INCLUDES)
	$(CC) -c $(CFLAGS) $<  

clean:
	rm $(OBJECTS) $(TARGET_LIB) Output.txt
