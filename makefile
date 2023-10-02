CC = g++
LD = $(CC)
CFLAGS = -std=c++17 -Wall -Wextra
LFLAGS = -Wall 

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

CRCAL = crcalculator

all: $(CRCAL)

$(CRCAL): $(OBJ)
	$(LD) $(LFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o $(CRCAL)
