main: main.o
	gcc src/*.o -Wall -g -o sorting.out -lsfml-graphics -lsfml-window -lsfml-system

main.o:
	gcc -g -Wall -c src/main.c -o src/main.o

.PHONY: clean
clean:
	rm -rf src/*.o && rm -rf *.out