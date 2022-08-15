#include<iostream>

using namespace std;

uint8_t g_largeIt = 1;
#define MAP_SIZE (g_largeIt ? 40 : 8) 
// void getMap(const char *maprule, char map[MAP_SIZE], const char *ptr)
void getMap(const char *maprule, char map[], const char *ptr, uint8_t mapSize = MAP_SIZE)
{
    int i = 0;
    // while (isalnum(*maprule) )
    while (isalnum(*maprule) && i < mapSize - 1)
    {
        map[i++] = tolower(*maprule++);
    }
    map[i] = '\0';
    return;
}

int main() 
{
    const char mrule[] = "a0a1a2a3a4a5a6a7a8a9b0b1b2b3b4b5b6b7b8b9c0c1c2c3c4c5.akamai.net";
    char hmap[MAP_SIZE];
    const char test[] = "1234567890987654321";
    getMap(mrule, hmap, test);
    cout << "Returned map is \'" << hmap << "\'" << endl;
    cout << "Test value is \'" << test << "\'" << endl;
    assert(sizeof(hmap) <= MAP_SIZE);
    return 0;
}