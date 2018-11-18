all: main.c
	gcc main.c

run: a.out
	./a.out

clean:
	rm *.out