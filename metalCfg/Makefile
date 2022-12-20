.PHONY = run

run: clean metalCfg
	./bin/metalCfg

metalCfg: ./src/metalCfg.cpp
	g++ --std=c++20 -L/opt/homebrew/opt/boost/lib -I/opt/homebrew/opt/boost/include -Werror -Wall -o ./bin/metalCfg ./src/metalCfg.cpp

clean:
	rm -rf ./bin/metalCfg