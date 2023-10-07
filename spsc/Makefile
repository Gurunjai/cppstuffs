.PHONY = run

PATH=/opt/homebrew
CXX:=g++
CXXFLAGS:=--std=c++20 -Werror -Wall -I$(PATH)/include/
LDFLAGS:=-L$(PATH)/lib/ -lboost_thread-mt

run: clean spsc
	./bin/spsc

spsc: ./src/spsc.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o ./bin/spsc ./src/spsc.cpp

clean:
	rm -rf ./bin/spsc