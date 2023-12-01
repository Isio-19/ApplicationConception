all: 
	g++ -I "C:\SFML-2.6.1\include" -c main.cpp -o main.o
	g++ -L "C:\SFML-2.6.1\lib" .\main.o -o main.exe -lmingw -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows
	./main