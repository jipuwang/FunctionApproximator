main: main.cpp parser.cpp parser.hpp linearizer.cpp linearizer.hpp utils.hpp
	g++ main.cpp parser.cpp linearizer.cpp -std=c++11 -Wall -o main.exe 