.PHONY = run

run: clean xmlparse
	./bin/xmlparse

xmlparse: ./src/xmlParse.cpp
	g++ --std=c++20 -Werror -Wall -lxml2 -I/opt/homebrew/opt/libxml2/include -o ./bin/xmlparse ./src/xmlParse.cpp

clean:
	rm -rf ./bin/xmlparse