all: main

main: main.o window.o character.o map.o game.o
	g++ main.o window.o character.o map.o game.o -o main.app -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -std=c++17

main.o: main.cpp
	g++ -c main.cpp

window.o: window.cpp
	g++ -c window.cpp

character.o: character.cpp
	g++ -c character.cpp

map.o: map.cpp
	g++ -c map.cpp

game.o: game.cpp
	g++ -c game.cpp

clean:
	rm main.o window.o character.o map.o game.o
