
compile: main.cxx FixedPoint.h 
	clang++ ${file} -o ${output} -std=c++17 -lc++ -I . -g -fdiagnostics-color=always