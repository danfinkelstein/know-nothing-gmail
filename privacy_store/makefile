OBJECTS = lineb.o lookup.o match.o

.c.o:
	g++ -c -O -finline-functions $*.cc

lookup: $(OBJECTS)
	g++ $(OBJECTS)
	cp a.out lookup
	rm a.out
make:
	makemake +g++ -O -finline-functions lookup

lineb.o: lineb.cc lineb.h
lookup.o: lineb.h lookup.cc match.h
match.o: match.cc match.h
