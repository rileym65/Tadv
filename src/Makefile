CC = gcc
CFLAGS =
LFLAGS =
DEFS =
INCDIR =
INCS =
LIBDIR =
LIBS =
OBJS = \
	actions.o \
	crypt.o \
	init.o \
	load.o \
	main.o \
	save.o \
	util.o

tadv: $(OBJS)
	$(CC) $(LFLAGS) $(LIBDIR) $(LIBS) $(OBJS) -o tadv

.c.o:
	$(CC) $(CFLAGS) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm tadv

actions.o: header.h actions.c
crypt.o:   header.h crypt.c
init.o:    header.h init.c
load.o:    header.h load.c
main.o:    header.h main.c
save.o:    header.h save.c
util.o:    header.h util.c

