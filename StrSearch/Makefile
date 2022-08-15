.PHONY=run

run: clean searcher
	./bin/searcher
	
searcher: src/main.cpp
	g++ -Wall -Werror -std=c++20 -o ./bin/searcher ./src/main.cpp

clean:
	rm -rf ./bin/searcher

