INCDIRS:=/Users/dmielke/Documents/oopl/trees/googletest/googletest/include
LIBDIRS:=/Users/dmielke/Documents/oopl/trees/googletest/googletest/make

FILES :=                                \
    .travis.yml                         \
    dijkstra-tests/EID-RunBearAndPoker.in   \
    dijkstra-tests/EID-RunBearAndPoker.out  \
    dijkstra-tests/EID-TestBearAndPoker.c++ \
    dijkstra-tests/EID-TestBearAndPoker.out \
    BearAndPoker.c++                        \
    BearAndPoker.h                          \
    BearAndPoker.log                        \
    html                                \
    RunBearAndPoker.c++                     \
    RunBearAndPoker.in                      \
    RunBearAndPoker.out                     \
    TestBearAndPoker.c++                    \
    TestBearAndPoker.out                    \
    BearAndPokerBundle.c++

# Call gcc and gcov differently on Darwin
ifeq ($(shell uname), Darwin)
  CXX      := g++
  GCOV     := gcov
  VALGRIND := echo Valgrind not available on Darwin
else
  CXX      := g++-4.8
  GCOV     := gcov-4.8
  VALGRIND := valgrind
endif

CXXFLAGS   := -pedantic -std=c++11 -Wall -I$(INCDIRS)
LDFLAGS    := -lgtest -lgtest_main -pthread -L$(LIBDIRS)
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunBearAndPoker
	rm -f RunBearAndPoker.tmp
	rm -f TestBearAndPoker
	rm -f TestBearAndPoker.tmp
	rm -f BearAndPokerBundle

config:
	git config -l

bundle:
	cat BearAndPoker.h BearAndPoker.c++ RunBearAndPoker.c++ | sed -e "s/#include \"BearAndPoker.h\"//g" > BearAndPokerBundle.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) BearAndPokerBundle.c++ -o BearAndPokerBundle

scrub:
	make  clean
	rm -f  BearAndPoker.log
	rm -rf dijkstra-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunBearAndPoker.tmp TestBearAndPoker.tmp

RunBearAndPoker: BearAndPoker.h BearAndPoker.c++ RunBearAndPoker.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) BearAndPoker.c++ RunBearAndPoker.c++ -o RunBearAndPoker

RunBearAndPoker.tmp: RunBearAndPoker
	./RunBearAndPoker < RunBearAndPoker.in > RunBearAndPoker.tmp
	diff RunBearAndPoker.tmp RunBearAndPoker.out

TestBearAndPoker: BearAndPoker.h BearAndPoker.c++ TestBearAndPoker.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) BearAndPoker.c++ TestBearAndPoker.c++ -o TestBearAndPoker $(LDFLAGS)

TestBearAndPoker.tmp: TestBearAndPoker
	./TestBearAndPoker                                                     >  TestBearAndPoker.tmp 2>&1
	$(VALGRIND) ./TestBearAndPoker                                         >> TestBearAndPoker.tmp
	$(GCOV) -b BearAndPoker.c++     | grep -A 5 "File 'BearAndPoker.c++'"     >> TestBearAndPoker.tmp
	$(GCOV) -b TestBearAndPoker.c++ | grep -A 5 "File 'TestBearAndPoker.c++'" >> TestBearAndPoker.tmp
	cat TestBearAndPoker.tmp
