.PHONY = run

run: clean frnd
	./bin/frnd

frnd: ./src/frnd.cpp
	g++ --std=c++11 -Werror -Wall -o ./bin/frnd ./src/frnd.cpp

clean:
	rm -rf ./bin/frnd