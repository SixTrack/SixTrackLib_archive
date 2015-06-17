CC= gcc
CFLAGS= -Wall -Werror -fpic
LDFLAGS= -shared
SRCS = kick2d.c rot2d.c counter.c loop.c results.c
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
	rm $(OBJECTS) $(TARGET_LIB)
