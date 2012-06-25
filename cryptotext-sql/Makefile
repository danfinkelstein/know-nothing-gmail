##
## $Id: Makefile 83 2010-09-19 18:30:14Z df2417 $
##
##

CXX = g++
CXXFLAGS = -g
#LIBS = -I../include -L../lib -lsqlite3 -lm -lcrypto
LIBS = -lsqlite3 -lm -lcrypto

.SUFFIXES: .o .h .cc .c

all: main HTMLStripper

ReplaceAll.o: ReplaceAll.cc ReplaceAll.h require.h

HTMLStripper.o: HTMLStripper.cc require.h ReplaceAll.h

HTMLStripper: HTMLStripper.o ReplaceAll.o
	$(CXX) $(CXXFLAGS) $^ -o $@

misc_text_tools: misc_text_tools.o GeneralHashFunctions.o base64.o
	$(CXX) $(CXXFLAGS) $^ -lcrypto -o $@

## Target: main with LiMiT
limit: main.o misc_text_tools.o GeneralHashFunctions.o base64.o
	$(CXX) $(CXXFLAGS) $(LIBS) -DLIMIT $^ -llimit -o $@

## Target: main without LiMiT
main: main.o misc_text_tools.o GeneralHashFunctions.o base64.o
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $@

## Used when misc_text_tools includes a main() function
##misc_text_tools: misc_text_tools.o GeneralHashFunctions.o base64.o
##	$(CXX) $(CXXFLAGS) $^ -lcrypto -o $@

#### Clean target deletes all generated files ####
clean:
	-rm *.o main misc_text_tools HTMLStripper 

.c.o:
	$(CXX) $^ $(LIBS) -o $@

.cc.o:
	$(CXX) $(CXXFLAGS) $(LIBS) -c -o $*.o $<
