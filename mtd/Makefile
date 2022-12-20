.PHONY = run

run: clean mtd
	./bin/mtd

mtd: ./src/mtd.cpp
	g++ --std=c++20 -Werror -Wall -o ./bin/mtd ./src/mtd.cpp

clean:
	rm -rf ./bin/mtd