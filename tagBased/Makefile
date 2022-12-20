.PHONY = run

run: clean tagBased
	./bin/tagBased

tagBased: ./src/tagBased.cpp
	g++ --std=c++20 -Werror -Wall -o ./bin/tagBased ./src/tagBased.cpp

clean:
	rm -rf ./bin/tagBased