OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -std=c99 -g

all : test-sll test-dll test-s test-q

test-sll : integer.o sll.o test-sll.o
	gcc $(LOPTS) -o test-sll integer.o sll.o test-sll.o

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

test-sll.o : test-sll.c integer.h sll.h
	gcc $(OOPTS) test-sll.c

test-dll : integer.o dll.o test-dll.o
	gcc $(LOPTS) -o test-dll integer.o dll.o test-dll.o

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

test-dll.o : test-dll.c integer.h dll.h
	gcc $(OOPTS) test-dll.c

test-s : integer.o dll.o stack.o test-s.o
	gcc $(LOPTS) -o test-s integer.o dll.o stack.o test-s.o

stack.o : stack.c stack.h dll.h
	gcc $(OOPTS) stack.c

test-s.o : test-s.c integer.h dll.h stack.h
	gcc $(OOPTS) test-s.c

test-q : integer.o dll.o queue.o test-q.o
	gcc $(LOPTS) -o test-q integer.o sll.o queue.o test-q.o

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

test-q.o : test-q.c integer.h sll.h queue.h
	gcc $(OOPTS) test-q.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

test : test-sll test-dll test-s test-q
	./test-sll
	./test-dll
	./test-s
	./test-q

clean   :
	rm -f integer.o sll.o test-sll.o test-sll dll.o test-dll.o test-dll stack.o test-s.o test-s queue.o test-q.o test-q
