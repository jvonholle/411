all: huffcode.o huffcode_test.o
	g++ -std=c++11 -Wall -pedantic huffcode.o huffcode_test.o
huffcode.o: huffcode.cpp huffcode.hpp
	g++ -std=c++11 -Wall -pedantic -c huffcode.cpp huffcode.hpp
huffcode_test.o: huffcode_test.cpp
	g++ -std=c++11 -Wall -pedantic -c huffcode_test.cpp huffcode.hpp