OBJS = scanner.o integer.o real.o string.o comparator.o reader.o sll.o dll.o stack.o queue.o sqsort.o -o sqsort
OOPTS = -Wall -Wextra -std=c99 -g -c
LOPTS = -Wall -Wextra -std=c99 -g

all : sqsort

sqsort : scanner.o integer.o real.o string.o comparator.o reader.o sll.o dll.o stack.o queue.o sqsort.o
	gcc $(LOPTS) $(OBJS)

sqsort.o : sqsort.c integer.h sll.h dll.h stack.h queue.o
	gcc $(OOPTS) sqsort.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

comparator.o : comparator.c comparator.h
	gcc $(OOPTS) comparator.c

reader.o : reader.c reader.h
	gcc $(OOPTS) reader.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

stack.o : stack.c stack.h dll.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

test : sqsort
	./sqsort -v
	./sqsort -d test-d.txt
	./sqsort -r test-r.txt
	./sqsort -s test-s.txt
clean   :
	rm -f scanner.o integer.o real.o string.o comparator.o sll.o dll.o stack.o queue.o sqsort.o sqsort
