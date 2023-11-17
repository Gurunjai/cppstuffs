.PHONY = run

run: clean atomicUdt
	./bin/atomicUdt

atomicUdt: ./src/AtomicUdt.cpp
	g++ --std=c++17 -Werror -Wall -o ./bin/atomicUdt ./src/AtomicUdt.cpp

clean:
	rm -rf ./bin/atomicUdt