all: build.o build_test2.o
	g++ -std=c++11 -Wall -pedantic build.o build_test2.o 
build.o: build.cpp build.h
	g++ -std=c++11 -Wall -pedantic -c build.cpp build.h
build_test2.o: build_test2.cpp
	g++ -std=c++11 -Wall -pedantic -c build_test2.cpp build.h