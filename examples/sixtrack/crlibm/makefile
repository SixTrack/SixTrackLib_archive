OBJ1:= csh_fast.o trigo_fast.o tan.o sine.o cosine.o exp.o exp_fast.o logsix.o log_fast.o log10.o atan.o atan_fast.o
OBJ2:= addition_scs.o double2scs.o multiplication_scs.o division_scs.o scs2double.o zero_scs.o
OBJS := $(OBJ1) $(OBJ2) ericc.o disable_xp.o enable_xp.o round_near.o dtoaf.o dtoa_c.o rem_pio2.o

HEAD1:= crlibm.h crlibm_private.h scs.h scs_config.h scs_private.h crlibm_config.h
HEAD2:= scs.h scs_config.h scs_private.h

AM1_CFLAGS:= -fPIC -std=c99 -Wall -Wshadow -Wpointer-arith  -Wcast-align -Wconversion -Waggregate-return -Wstrict-prototypes -Wnested-externs -Wlong-long -Winline -pedantic -fno-strict-aliasing
AM2_CFLAGS:= -Wall -Wshadow -Wpointer-arith -Wcast-align -Wconversion -Waggregate-return -Wstrict-prototypes -Wnested-externs -Wlong-long -Winline
DEFS:= -DLINUX_INLINE -DHAVE_CONFIG_H -I.
CFLAGS:= -g -O2 -m32

CC:= gcc
COMPILE1:= $(CC) $(DEFS) $(AM1_CFLAGS) $(CFLAGS)
COMPILE2:= $(CC) $(DEFS) $(AM2_CFLAGS) $(CFLAGS)

crlibm.a: $(OBJS)
	ar -rv $@ $(OBJS)

$(OBJ1): %.o: %.c %.h $(HEAD1)
	$(COMPILE1) -o $@ -c $<

$(OBJ2): %.o: %.c $(HEAD2)
	$(COMPILE2) -o $@ -c $<

rem_pio2.o: rem_pio2.c coefpi2.h $(HEAD1)
	$(COMPILE1) -o $@ -c $<

ericc.o: ericc.c crlibm.h crlibm_private.h
	$(COMPILE1) -o $@ -c $<

enable_xp.o: enable_xp.c
	$(COMPILE1) -o $@ -c $<

round_near.o: round_near.c
	$(CC) -m32 -std=c99 -W -Wall -pedantic -o $@ -c $<

dtoa_c.o: dtoa_c.c
	$(CC) -m32 -std=c99 -W -Wall -pedantic -o $@ -c $<



