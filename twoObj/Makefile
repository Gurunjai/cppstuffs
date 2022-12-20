.PHONY = run

run: clean twoobj
	./bin/twoobj

twoobj: ./src/twoObj.cpp
	g++ --std=c++20 -Werror -Wall -o ./bin/twoobj ./src/twoObj.cpp

clean:
	rm -rf ./bin/twoObj