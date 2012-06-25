CFLAGS=-O3 -g -Ipebil/include -Ipebil/external/udis86-1.7/ -I/lib/modules/`uname -r`/build/include -I../include
CXXFLAGS=$(CFLAGS)
LDFLAGS=-Lpebil/bin -lpebil -Lpebil/external/udis86-1.7/lib -ludis86 -lboost_program_options
CPP=g++


all: mutator

mutator: mutator.o InstrMutator.o asm64.o pebil/bin/libpebil.a pebil/external/udis86-1.7/lib/libudis86.a
	$(CPP) -o $@ asm64.o mutator.o InstrMutator.o $(LDFLAGS) 

pebil/bin/libpebil.a:
	cd pebil/src; make

asm64.o: asm64.S
	gcc -c -o $@ asm64.S

clean:
	rm -f *.o mutator
