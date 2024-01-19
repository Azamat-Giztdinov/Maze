CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wextra
OS := $(shell uname)
TESTFILE = tests/unit_tests.cc model/mazemodel.cpp

ifeq ($(OS),Linux)
FLAGS = -lgtest -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
PROG = Maze
FYLE = view/$(PROG)
PROGOPEN = ./build/$(PROG)

else
FLAGS = -lgtest -lm -lpthread -fprofile-arcs -ftest-coverage
PROG = Maze.app
FYLE = view/$(PROG)
PROGOPEN = ./build/$(PROG)/Contents/MacOS/maze
endif

all: install open

install: uninstall
	make clean
	mkdir build
	cd view && qmake && make -j6 && make clean && rm Makefile && cd ../ && mv $(FYLE) build

uninstall:
	rm -rf build/

clean:
	@rm -rf *.o *.a unit_test
	@rm -rf *.gcno *gcda *.gcov gcov
	@rm -rf report report.info
	@rm -rf *.dSYM
	@rm -rf ./view/.qmake.stash


dvi: 
	@open description/dvi.md

dist:
	rm -rf Archive_Maze/
	mkdir Archive_Maze/
	mkdir Archive_Maze/src
	cp -r ./build/$(PROG) Archive_Maze/src/
	tar cvzf Archive_Maze.tgz Archive_Maze/
	rm -rf Archive_Maze/

tests: clean
	$(CC) $(CFLAGS) $(TESTFILE) $(FLAGS) -o unit_test
	./unit_test

leak:
	leaks --atExit -- $(PROGOPEN)

open:
	$(PROGOPEN)

clang:
	find . \( -name '*.h' -o -name '*.cc' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -style=Google -n
