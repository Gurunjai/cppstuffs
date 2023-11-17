.PHONY = run

# PATH=/opt/homebrew
CXX:=g++
CXXFLAGS:=--std=c++20 -Werror -Wall 
# CXXFLAGS:=--std=c++20 -Werror -Wall -I$(PATH)/include/
# LDFLAGS:=-L$(PATH)/lib/ -lboost_thread-mt
LDFLAGS:= -lpthread

run: clean StackDemo
	./bin/StackDemo

StackDemo: ./src/StackDemo.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o ./bin/StackDemo ./src/StackDemo.cpp

clean:
	rm -rf ./bin/StackDemo