main: main.o
	g++ *.o -Wall -g -o sorting.out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
main.o:
	g++ -Wall -c -o main.o main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.PHONY: clean
clean:
	rm -rf src/*.o && rm -rf *.out