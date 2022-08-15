.PHONY = run

run: clean testup
	./bin/testup

testup: ./src/main.cpp
	g++ -std=c++20 -Wall -Werror -o ./bin/testup ./src/main.cpp

clean:
	rm -rf ./bin/testup
