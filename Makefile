main: main.cpp util.hpp quicksort.hpp
	g++ -std=c++11 -O0 $< -o $@
