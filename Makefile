all: 
	g++ -c main.cpp
	g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system
	./main

test: 
	g++ -c main_test.cpp -o main.o  
	g++ main.o MVC/Model.cpp MVC/View.cpp MVC/Controller.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system 
	./main

clean:
	rm main.o
	rm main