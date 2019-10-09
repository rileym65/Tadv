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
	file.o \
	init.o \
	main.o \
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
file.o:    header.h file.c
init.o:    header.h init.c
main.o:    header.h main.c
util.o:    header.h util.c

