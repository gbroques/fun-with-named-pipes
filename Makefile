CFLAGS = -g -Wall -Wshadow
GCC = gcc $(CFLAGS)

all: proj3 program2

proj3: $(OBJS)
	$(GCC) -o proj3 proj3.c

program2: $(OBJS)
	$(GCC) -o program2 program2.c

clean:
	rm -f *.o a.out proj3 program2
