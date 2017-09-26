all: build.o build_test.o
	g++ -std=c++11 -Wall -pedantic build.o build_test.o build.h
build.o: build.cpp
	g++ -std=c++11 -Wall -pedantic -c build.cpp
build_test.o: build_test.cpp
	g++ -std=c++11 -Wall -pedantic -c build_test.cpp