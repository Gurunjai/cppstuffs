.PHONY = run

run: clean stdmaps
	./bin/stdmaps

stdmaps: ./src/stdmaps.cpp
	g++ --std=c++17 -Werror -Wall -o ./bin/stdmaps ./src/stdmaps.cpp

clean:
	rm -rf ./bin/stdmaps