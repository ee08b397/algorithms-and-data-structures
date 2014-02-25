.PHONY: clean
CC=g++
CFLAGS=-c -v -Wall -O2 #-DDEBUGGING_OUTPUT    # print debugging output if necessary
LDFLAGS=
SRC=triangle.cc rectangle.cc circle.cc area_visitor.cc test.cc
OBJ=$(SRC:.cc=.o)
TEST=test

.cc.o:
	$(CC) $(CFLAGS) $<

all: $(TEST)

debug: $(DEBUG)

$(TEST): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@
	
clean:
	rm -f *.o $(TEST)
