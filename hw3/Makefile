all: contigsum_test.o inversions_test.o
	g++ -std=c++11 contigsum_test.o contigsum.hpp -o contig.o && g++ -std=c++11 inversions_test.o inversions.hpp -o inver.o
contigsum_test.o: contigsum_test.cpp
	if [ -f contigsum.hpp.gch ]; then rm contigsum.hpp.gch; fi && g++ -std=c++11 -Wall -pedantic -c contigsum_test.cpp
inversions_test.o: inversions_test.cpp inversions.hpp
	if [ -f inversions.hpp.gch ]; then rm inversions.hpp.gch; fi && g++ -std=c++11 -Wall -pedantic -c inversions_test.cpp 