all:
	gcc -c triangle.c
	g++ -c *.cpp
	g++ -o progetto.bin *.o

refiner: TriangleRefiner.cpp TriangleRefiner.hpp
	g++ -c TriangleRefiner.cpp
	g++ -o progetto.bin *.o

clean:
	rm *.o

cleanall:
	rm *.o progetto.bin