CC=g++
CFLAGS=-std=c++11 -O2

SOURCES=$(addprefix src/, graph.cpp input.cpp)
MAIN_SOURCES=$(addprefix src/, main.cpp)
TEST_SOURCES=$(addprefix src/, tests.cpp)
INCLUDE=include/
DIST=dist
MAIN=main
TESTS=tests

all: main tests

$(MAIN): $(MAIN_SOURCES) $(SOURCES) 
	$(CC) -I $(INCLUDE) $(CFLAGS) $^ -o $(DIST)/$@

$(TESTS): $(TEST_SOURCES) $(SOURCES)
	$(CC) -I $(INCLUDE) $(CFLAGS) $^ -o $(DIST)/$@

clean:
	rm -f $(DIST)/$(MAIN) $(DIST)/$(TESTS)
