CC=gcc
CFLAGS=-Wall -lm

SRC=src/main.c src/distance.c src/planner.c src/utils.c

OUT=drone

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

run:
	./drone
