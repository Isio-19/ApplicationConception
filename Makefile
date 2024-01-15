all: 
	g++ -c main.cpp -o main.o  
	g++ main.o MVC/*.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system 
	./main
	make clean 

clean:
	rm main.o
	rm main