#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using uint = unsigned int;
class hash_map
{
    std::vector<int> data;

public:
    hash_map(size_t n) {
        data = std::vector<int>(n, -1);
    }

    void insert(uint value) {
        int n = data.size();
        data[value % n] = value;
        std::cout << "Inserted " << value << std::endl;
    }

    bool find(uint value) {
        int n = data.size();
        return (data[value % n] == value);
    }

    void erase(uint value) {
        int n = data.size();
        if (data[value % n] == value) {
            data[value % n] = -1;
            std::cout << "Removed " << value << std::endl;
        }
    }

    void dump() {
        for (auto s : data) {
            std::cout << s << "  ";
        }

        std::cout << std::endl;
    }
};

class list_hash_map
{
    std::vector<std::list<int>> data;

public:
    list_hash_map(size_t n) {
        data.resize(n);
    }

    void insert(uint value) {
        int n = data.size();
        data[value % n].push_back(value);
        std::cout << "Inserted " << value << std::endl;
    }

    bool find(uint value) {
        int n = data.size();
        auto entries = data[value % n];
        return std::find(entries.begin(), entries.end(), value) != entries.end();
    }

    void erase(uint value) {
        int n = data.size();
        auto entries = data[value % n];
        auto iter = std::find(entries.begin(), entries.end(), value);

        if (iter != entries.end()) {
            entries.erase(iter);
            std::cout << "Removed " << value << std::endl;
        }
    }

    void dump() {
        uint cnt = 0;
        for (auto s : data) {
            std::cout << "Index " << cnt << "   ";
            for (auto i : s) {
                std::cout << i << "   ";
            }
            cnt++;
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
};

void testHashMap() {
    hash_map map(7);
    auto print = [&](int value) {
        if (map.find(value)) {
            std::cout << value << " found in the map";
        } else {
           std::cout << value << " not found in the map";
        }

        std::cout << std::endl;
    };

    map.insert(2);
    map.insert(25);
    map.insert(49);
    print(25);

    map.insert(4);
    map.insert(290);
    
    print(25);
    print(49);
    print(100);

    map.insert(100);
    print(100);
    map.erase(25);
}

void testListHashMap() {
    list_hash_map map(7);
    auto print = [&](int value) {
        if (map.find(value)) {
            std::cout << value << " found in the map";
        } else {
           std::cout << value << " not found in the map";
        }

        std::cout << std::endl;
    };

    map.insert(2);
    map.insert(25);
    map.insert(49);
    print(25);

    map.insert(4);
    map.insert(290);
    
    print(25);
    print(49);
    print(100);

    map.insert(100);
    print(100);
    map.erase(25);
}

int main() {
    std::cout << "Testing Hash Map " << std::endl << std::endl;
    testHashMap();
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "Testing List Hash Map " << std::endl << std::endl;
    testListHashMap();
    return 0;
}