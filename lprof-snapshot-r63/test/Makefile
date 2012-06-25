CFLAGS=-I/lib/modules/`uname -r`/build/include -I../instr/kernel -I../include	\
	-g -O0 -save-temps -Wall -pthread
LDFLAGS=-llprofm -lm -pthread -L../src/
PCFLAGS=-g -save-temps -O0
FC=gfortran

PROGS=  manual1 
# kernel_direct_test pdebug test \
# 	proftest proftestcpp proftestfortran \
# 	functions_test test_contextswitch kernel_thread_test1
all: $(PROGS)

test: test.o ../src/liblprof.a

kernel_direct_test2: kernel_direct_test2.o kernel_direct_test2_asm.o

kernel_direct_test2_asm.o: kernel_direct_test2_asm.S
	as -o kernel_direct_test2_asm.o kernel_direct_test2_asm.S

rttest: rttest.c
	gcc -O3 -o rttest rttest.c
test_contextswitch: test_contextswitch.o ../src/liblprof.a

functions_test: functions_test.o 
	$(CC) $(PCFLAGS) -o $@ $^
functions_test.o: functions_test.c 
	$(CC) $(PCFLAGS) -c -o $@ $^
functions_test.c: functions_test.py
	./functions_test.py > functions_test.c

proftest: proftest.o 
	$(CC) $(PCFLAGS) -o $@ $^
proftest.o: proftest.c 
	$(CC) $(PCFLAGS) -O0 -fno-inline -c -o $@ $^

proftestcpp: proftestcpp.o 
	$(CXX) $(PCFLAGS) -o $@ $^
proftestcpp.o: proftestcpp.cpp
	$(CXX) $(PCFLAGS) -c -o $@ $^

proftestfortran: proftestfortran.o
	$(FC) $(PCFLAGS) -o $@ $^
proftestfortran.o: proftestfortran.f
	$(CXX) $(PCFLAGS) -c -o $@ $^

clean:
	rm -f *.o *.i *.ii *.mod *.s functions_test.c $(PROGS)

%: %.o
	$(CC) $^ $(LDFLAGS) -o $@

%: %.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@