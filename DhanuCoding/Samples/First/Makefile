.PHONY = run

run: clean main
	./bin/main

main: ./src/main.cpp
	g++ --std=c++20 -o ./bin/main ./src/main.cpp

clean:
	rm -rf ./bin/main