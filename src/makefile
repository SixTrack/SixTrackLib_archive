CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared  # linking flags
LIBS = -lm  # linking flags
RM = rm -f  # rm command

SRCS = rot2d.c # source files
OBJS = $(SRCS:.c=.o)
TARGET_LIB = $(SRCS:.c=.so) # target lib
TARGET_EXE = $(SRCS:.c=) # target lib

.PHONY: all clean
all: ${TARGET_LIB} ${TARGET_EXE}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(TARGET_EXE): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
