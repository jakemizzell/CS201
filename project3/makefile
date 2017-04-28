OBJS = dijkstra.o binomial.o darray.o vertex.o sll.o queue.o integer.o scanner.o -o dijkstra
OOPTS = -Wall -Wextra -std=c99 -g -c
LOPTS = -Wall -Wextra -std=c99 -g

all : dijkstra

dijkstra : dijkstra.o binomial.o darray.o vertex.o sll.o queue.o integer.o scanner.o
	gcc $(LOPTS) $(OBJS)

dijkstra.o : dijkstra.c binomial.h darray.h vertex.h
	gcc $(OOPTS) dijkstra.c

binomial.o : binomial.c binomial.h
	gcc $(OOPTS) binomial.c

darray.o : darray.c darray.h
	gcc $(OOPTS) darray.c

vertex.o : vertex.c vertex.h
	gcc $(OOPTS) vertex.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

test : dijkstra
	./dijkstra input.txt

clean :
	rm -f dijkstra.o binomial.o darray.o vertex.o sll.o queue.o integer.o real.o string.o comparator.o read.o scanner.o dijkstra
