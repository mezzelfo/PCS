all:
	gcc -c triangle.c
	g++ -c -std=c++11 *.cpp
	g++ -o progetto.bin *.o

refiner: TriangleCell.cpp TriangleCell.hpp TriangleRefiner.cpp TriangleRefiner.hpp
	g++ -c -std=c++11 TriangleCell.cpp TriangleRefiner.cpp main.cpp
	g++ -o progetto.bin *.o

clean:
	rm *.o

cleanall:
	rm *.o progetto.bin