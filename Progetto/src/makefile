all:
	gcc -c triangle.c
	g++ -c -std=c++11 *.cpp
	g++ -o progetto.bin *.o

refiner: TriangleRefiner.cpp TriangleRefiner.hpp
	g++ -c TriangleRefiner.cpp main.cpp
	g++ -o progetto.bin *.o

clean:
	rm *.o

cleanall:
	rm *.o progetto.bin