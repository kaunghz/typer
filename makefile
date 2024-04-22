STD=--std=c++17
GCC=g++
BIN=bin
OBJ=obj

bin/typer: src/main.cpp src/colors.h
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${GCC} ${STD} -o bin/typer src/main.cpp

cpp: bin/typer
	./bin/typer cpp

py: bin/typer
	./bin/typer py

.PHONY: doc
doc:
	doxygen config
	cd latex && make

clean:
	rm -f bin/*
	rm -rf bin
	rm -r -f result/*