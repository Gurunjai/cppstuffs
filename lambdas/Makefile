.PHONY = run

run: clean lambdas
	./bin/lambdas

lambdas: ./src/lambdas.cpp
	g++ --std=c++20 -Werror -Wall -o ./bin/lambdas ./src/lambdas.cpp

clean:
	rm -rf ./bin/lambdas