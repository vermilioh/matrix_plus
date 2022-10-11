CXX =g++ --std=c++17
FLAGS = -Wall -Werror -Wextra
OS=$(shell uname)
GCOV=-fprofile-arcs -ftest-coverage

ifeq ($(OS), Linux)
  LIBS=-lgtest -lpthread -L/usr/lib
  LEAKS=valgrind ./matrix_test.out
else
  LIBS=-lgtest
  LEAKS=CK_FORK=no leaks --atExit -- ./matrix_test.out
endif

all: clean matrix_oop.a test

test: clean matrix_oop.a 
	$(CXX) $(FLAGS) test.cpp matrix_oop.a $(LIBS) -o matrix_test.out 
	./matrix_test.out

matrix_oop.a: 
	$(CXX) $(FLAGS) -c matrix_oop.cpp -o matrix_oop.o
	ar rcs matrix_oop.a matrix_oop.o

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out 
	rm -rf ./report *.dSYM

leaks: test
	$(LEAKS)
	make clean
	
style: 
	cp linters/clang-format .
	clang-format -n *.cpp *.h
	rm clang-format

cppcheck:
	cppcheck --language=c++ *.cpp *.h

gcov_report:
	$(CXX) $(GCOV) test.cpp matrix_oop.cpp $(LIBS) -o GCOV_test.out
	./GCOV_test.out
	lcov -t "GCOV_test" -o GCOV_test.info -c -d . --no-external
	genhtml -o report GCOV_test.info
	open -a "Google Chrome" report/index.html
