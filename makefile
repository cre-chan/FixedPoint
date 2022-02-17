
compile: main.cxx FixedPoint.cxx 
	clang++ ./main.cxx -o main.out -std=c++17 -lc++ -I . -g -fdiagnostics-color=always