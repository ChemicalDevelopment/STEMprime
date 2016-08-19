MAIN_SOURCES = ./main/stemprime.c

FACTOR_SOURCES = ./factor/main.c ./factor/factor.c ./factor/factor.h   

LIB = -lm -lgmp

all: main_o factor_o

main_o: ; gcc $(MAIN_SOURCES) $(LIB) -o ./out/main.o

factor_o: ; gcc $(FACTOR_SOURCES) $(LIB) -o ./out/factor.o

clean: ; rm ./out/main.o ./out/factor.o
