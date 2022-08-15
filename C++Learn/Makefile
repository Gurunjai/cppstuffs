.PHONY=run

run: clean learn
	./bin/learn

learn: src/main.cpp
	g++ -Wall -Werror -std=c++20 -o ./bin/learn ./src/main.cpp

clean:
	rm -rf ./bin/learn