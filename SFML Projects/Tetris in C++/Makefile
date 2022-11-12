main: main.o
	g++ *.o -Wall -g -o tetris.out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
main.o: game.o button.o
	g++ -Wall -c -o main.o main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
button.o:
	g++ -Wall -c -o src/button.o src/button.cpp -lsfml-graphics -lsfml-window -lsfml-system
game.o: board.o piece.o
	g++ -Wall -c -o src/game.o src/game.cpp
board.o: linked_list.o piece.o
	g++ -Wall -c -o src/board.o src/board.cpp
linked_list.o:
	g++ -Wall -c -o src/linked_list.o src/linked_list.cpp
piece.o:
	g++ -Wall -c -o src/piece.o src/piece.c
.PHONY: clean
clean:
	rm -rf *.o && rm -rf src/*.o && rm -rf main && rm tetris.out