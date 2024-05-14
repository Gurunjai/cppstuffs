.PHONY = all

run: main
	./bin/main

main: clean
	g++ -o ./bin/main --std=c++14 -fsanitize=leak -g -shared-libsan ./src/main.cpp

clean:
	rm -rf ./bin/main