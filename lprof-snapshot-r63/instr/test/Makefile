CFLAGS=-O0 -save-temps -I/lib/modules/`uname -r`/build/include -I../kernel -pthread
LDFLAGS=-pthread
ASFLAGS=-g

all: test1 test1.instr test1.dis test1.instr.dis thread_tls thread_tls.dis

test1.dis: test1
	objdump -d -x test1 > test1.dis

test1.instr.dis: test1.instr
	objdump -d -x test1.instr > test1.instr.dis

test1.instr: test1
	../mutator test1 test1.instr

test1: test1.o test1_asm.o

thread_tls.dis: thread_tls
	objdump -d thread_tls > thread_tls.dis

thread_tls: thread_tls.o

clean:
	rm *.o
