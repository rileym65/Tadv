CC = gcc
CFLAGS =
LFLAGS =
DEFS =
INCDIR =
INCS =
LIBDIR =
LIBS =
OBJS = \
	actionblock.o \
	addequate.o \
	addflag.o \
	addword.o \
	carrying.o \
	checkactions.o \
	checkobjects.o \
	checkroomactions.o \
	containerscore.o \
	containerweight.o \
	crypt.o \
	doorsinroom.o \
	dropitem.o \
	encodefile.o \
	extract.o \
	fileread.o \
	getcode.o \
	getitem.o \
	getitemnumber.o \
	getroomnumber.o \
	gettoken.o \
	getvalue.o \
	init.o \
	load.o \
	main.o \
	mainloop.o \
	nextword.o \
	numberforitem.o \
	performaction.o \
	pop.o \
	prepass.o \
	printtoken.o \
	processleave.o \
	push.o \
	putintocontainer.o \
	putintoinventory.o \
	putintoroom.o \
	readaction.o \
	readactionsteps.o \
	readadventure.o \
	readdest.o \
	readdoor.o \
	readfile.o \
	readfunction.o \
	readitem.o \
	readmessage.o \
	readroom.o \
	removeitem.o \
	reset.o \
	save.o \
	score.o \
	takefromcontainer.o \
	takefrominventory.o \
	takefromroom.o \
	tokenize.o \
	tokenizeadd.o \
	trim.o \
	upper.o \
	weight.o

tadv: $(OBJS)
	$(CC) $(LFLAGS) $(LIBDIR) $(LIBS) $(OBJS) -o tadv

.c.o:
	$(CC) $(CFLAGS) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm tadv

actionblock.o:       header.h actionblock.c
addequate.o:         header.h addequate.c
addflag.o:           header.h addflag.c
addword.o:           header.h addword.c
carrying.o:          header.h carrying.c
checkactions.o:      header.h checkactions.c
checkobjects.o:      header.h checkobjects.c
checkroomactions.o:  header.h checkroomactions.c
containerscore.o:    header.h containerscore.c
containerweight.o:   header.h containerweight.c
crypt.o:             header.h crypt.c
doorsinroom.o:       header.h doorsinroom.c
dropitem.o:          header.h dropitem.c
encodefile.o:        header.h encodefile.c
extract.o:           header.h extract.c
fileread.o:          header.h fileread.c
getcode.o:           header.h getcode.c
getitem.o:           header.h getitem.c
getitemnumber.o:     header.h getitemnumber.c
getroomnumber.o:     header.h getroomnumber.c
gettoken.o:          header.h gettoken.c
getvalue.o:          header.h getvalue.c
init.o:              header.h init.c
load.o:              header.h load.c
main.o:              header.h main.c
mainloop.o:          header.h mainloop.c
nextword.o:          header.h nextword.c
numberforitem.o:     header.h numberforitem.c
performaction.o:     header.h performaction.c
pop.o:               header.h pop.c
prepass.o:           header.h prepass.c
printtoken.o:        header.h printtoken.c
processleave.o:      header.h processleave.c
push.o:              header.h push.c
putintocontainer.o:  header.h putintocontainer.c
putintoinventory.o:  header.h putintoinventory.c
putintoroom.o:       header.h putintoroom.c
readaction.o:        header.h readaction.c
readactionsteps.o:   header.h readactionsteps.c
readadventure.o:     header.h readadventure.c
readdest.o:          header.h readdest.c
readdoor.o:          header.h readdoor.c
readfile.o:          header.h readfile.c
readfunction.o:      header.h readfunction.c
readitem.o:          header.h readitem.c
readmessage.o:       header.h readmessage.c
readroom.o:          header.h readroom.c
removeitem.o:        header.h removeitem.c
reset.o:             header.h reset.c
save.o:              header.h save.c
score.o:             header.h score.c
takefromcontainer.o: header.h takefromcontainer.c
takefrominventory.o: header.h takefrominventory.c
takefromroom.o:      header.h takefromroom.c
tokenize.o:          header.h tokenize.c
tokenizeadd.o:       header.h tokenizeadd.c
trim.o:              header.h trim.c
upper.o:             header.h upper.c
weight.o:            header.h weight.c

