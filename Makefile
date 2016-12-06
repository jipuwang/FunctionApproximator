main: main.cpp parser.cpp parser.hpp linearizer.cpp linearizer.hpp utils.hpp
	g++ main.cpp parser.cpp linearizer.cpp -std=c++11 -Wall -lm -o main.exe 
run: 
	make
	./main.exe
plot:  
	make
	./main.exe
	python ./plotter.py
debug: main.cpp parser.cpp parser.hpp linearizer.cpp linearizer.hpp utils.hpp
	g++ main.cpp parser.cpp linearizer.cpp -std=c++11 -Wall -lm -g -o main.exe 
	gdb ./main.exe

