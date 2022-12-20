.PHONY = run

run: clean enabler
	./bin/enabler

enabler: ./src/enabler.cpp
	g++ --std=c++20 -Werror -Wall -o ./bin/enabler ./src/enabler.cpp

clean:
	rm -rf ./bin/enabler