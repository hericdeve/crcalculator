#Makefile para "CR Calculator"

CC = g++
LD = $(CC)
CFLAGS = -Wall 
LFLAGS = -Wall 

CRCALOBS = subject.o grade.o groupby.o cr.o

CRCAL = crcalculator

.cpp.o:
	$(CC) $(CFLAGS) -c $<


all:$(CRCAL)

crcalculator: $(CRCALOBS)
	$(LD) $(LFLAGS) -o $@ $(CRCALOBS)

clean:
	rm -f *.o $(CRCAL)
