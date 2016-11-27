MAIN_SOURCES = ./stemprime.c

LIB = -lm -lgmp

all: main test

main: $(MAIN_SOURCES)
	gcc $(MAIN_SOURCES) $(LIB) -o ./stemprime.o

test: 
	./stemprime.o 44497


clean: 
	rm ./stemprime.o
