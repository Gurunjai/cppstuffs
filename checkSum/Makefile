.PHONY = run

PATH=/opt/homebrew
CXX:=g++
CXXFLAGS:=--std=c++20 -Werror -Wall -I$(PATH)/include/
LDFLAGS:=-L$(PATH)/lib/ -lboost_thread-mt

run: clean ArrChecksum
	./bin/ArrChecksum

ArrChecksum: ./src/ArrChecksum.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o ./bin/ArrChecksum ./src/ArrChecksum.cpp

clean:
	rm -rf ./bin/ArrChecksum