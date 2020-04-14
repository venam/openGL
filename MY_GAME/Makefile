all: main

main:
	g++ *.cpp -c
	rm main.o
	g++ main.cpp  *.o  -lGL -lGLU -lglut -o main



clean:
	rm -f *.o
	rm -f main
