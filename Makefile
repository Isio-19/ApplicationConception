all: main model view controller
	g++ main.o Model.o View.o Controller.o -o main -lsfml-graphics -lsfml-window -lsfml-system 
	./main

main:
	g++ -c main.cpp -o main.o

model:
	g++ -c MVC/Model.cpp -o Model.o

view:
	g++ -c MVC/View.cpp -o View.o

controller:
	g++ -c MVC/Controller.cpp -o Controller.o

clean:
	rm *.o
	rm main