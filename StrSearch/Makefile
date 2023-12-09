.PHONY=run

run: clean searcher
	./bin/searcher
	
searcher: src/main.cpp
	# g++ -Wall -Werror -std=c++20 -o ./bin/searcher ./src/main.cpp 
	g++ -Wall -Werror -std=c++20 -o ./bin/searcher ./src/main.cpp -fsanitize=address -static-libsan -g

clean:
	rm -rf ./bin/searcher

