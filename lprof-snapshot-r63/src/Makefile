CFLAGS=-I/lib/modules/`uname -r`/build/include 	-I../include	\
	-g -O3 -save-temps -m64
CXXFLAGS=$(CFLAGS)
LDFLAGS=-m64
ASFLAGS=-m64 -I../include

all: liblprofm.a

liblprofm.a: lprof.o lprof_asm.o
	ar -crs $@ lprof_asm.o lprof.o

clean:
	rm -f *.o *.i *.a *.s

lprof.o: ../include/lprof.h