.PHONY = run

run: clean hashm
	./bin/hashm

hashm: ./src/hash.cpp
	g++ -std=c++20 -Wall -Werror -o ./bin/hashm ./src/hash.cpp

clean:
	rm -rf ./bin/*