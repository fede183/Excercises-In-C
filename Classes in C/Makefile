main: main.o
	gcc src/*.o -Wall -g -o animalSound.out

main.o: cow.o cat.o
	gcc -g -Wall -c src/main.c -o src/main.o

cow.o: animal.o
	gcc -g -Wall -c src/cow.c -o src/cow.o

cat.o: animal.o
	gcc -g -Wall -c src/cat.c -o src/cat.o

animal.o:
	gcc -g -Wall -c src/animal.c -o src/animal.o

.PHONY: clean
clean:
	rm -rf src/*.o && rm -rf *.out