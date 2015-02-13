CC=gcc
CFLAGS=-Wall -lm
objects=main.o dist.o swap.o permute.o free_2d.o route_dist.o shortest_route.o

task1: $(objects)
	$(CC) -o task1 $(objects) $(CFLAGS)

clean:
	$(RM) $(objects) task1 routes.txt
