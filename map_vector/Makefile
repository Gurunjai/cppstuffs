.PHONY = all

run: map_vector
	./bin/map_vector

map_vector: clean
	g++ -o ./bin/map_vector --std=c++17 ./src/map_vector.cpp

clean:
	rm -rf ./bin/map_vector