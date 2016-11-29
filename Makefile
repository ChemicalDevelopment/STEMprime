STEMPRIME_SOURCES = stemprime/src/main.c
STEMPRIME_OUT = stemprime.o

QS_SOURCES = quicksieve/src/*.c quicksieve/src/output/*.c quicksieve/src/sieves/*.c
QS_OUT = qs.o

LIB = -lm -lgmp

default: stemprime qs

all: stemprime qs

stemprime: $(STEMPRIME_SOURCES)
	gcc $(STEMPRIME_SOURCES) $(LIB) -Ofast -o $(STEMPRIME_OUT)

qs: $(QS_SOURCES)
	gcc $(QS_SOURCES) $(LIB) -Ofast -o $(QS_OUT)

test_stemprime: 
	$(STEMPRIME_OUT) 44497

clean: 
	rm $(STEMPRIME_OUT)
