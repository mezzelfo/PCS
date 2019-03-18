all:
	gcc -g -c triangle.c
	g++ -g -c -std=c++11 *.cpp
	g++ -g -o progetto.bin *.o

refiner: TriangleCell.cpp TriangleCell.hpp TriangleRefiner.cpp TriangleRefiner.hpp
	g++ -g -c -std=c++11 TriangleCell.cpp TriangleRefiner.cpp main.cpp
	g++ -g -o progetto.bin *.o

clean:
	rm *.o

cleanall:
	rm *.o progetto.bin