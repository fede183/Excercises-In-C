main: main.o
	g++ *.o -Wall -g -o main.out
main.o:
	g++ -Wall -c -o main.o main.c
.PHONY: clean
clean:
	rm -rf *.o && rm main.out