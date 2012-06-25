## -*- Makefile -*-
##
## $Id: Makefile 83 2010-09-19 18:30:14Z df2417 $
## 
##

CXX = g++
CXXFLAGS = -g
#LIBS = -I../include -L../lib -lsqlite3 -lm
LIBS = -lsqlite3 -lm

.SUFFIXES: .o .h .cc .c

all: main


## Target: main with LiMiT
limit: main.cc  
	$(CXX) $(CXXFLAGS) $? $(LIBS) -DLIMIT -llimit -o main

## Target: main without LiMiT
main: main.cc  
	$(CXX) $(CXXFLAGS) $? $(LIBS)  -o main

#### Clean target deletes all generated files ####
clean:
	-rm *.o main

.c.o:
	$(CXX) $^ $(LIBS) -o $@

.cc.o:
	$(CXX) $^ $(CXXFLAGS) $(LIBS) -c -o $*.o $<
#.cc.o:
#	$(CXX) $^ $(CXXFLAGS) $(LIBS) -o $@
