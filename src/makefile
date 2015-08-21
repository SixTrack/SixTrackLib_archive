CC= gcc
CFLAGS= -fpic -Wall -Werror
LDFLAGS= -shared
SRCS = results.c drift_exact.c multipole.c cavity.c align.c block.c drift.c extra.c
OBJECTS= $(SRCS:.c=.o)
TARGET_LIB= libtrack.so
INCLUDES= hmacro.h

.PHONY: all clean
all: $(TARGET_LIB)

test: $(TARGET_LIB)
	python track.py

$(TARGET_LIB): $(OBJECTS)
	$(CC) $(LDFLAGS) -o libtrack.so $(OBJECTS)

.c.o: $(INCLUDES)
	$(CC) -O3 -c $(CFLAGS) $<  

clean:
	rm $(OBJECTS) $(TARGET_LIB)