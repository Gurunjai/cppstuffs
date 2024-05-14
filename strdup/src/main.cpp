#include <iostream>
#include <unistd.h>

using namespace std;

struct tempNode
{
    tempNode() {
        srMap = strdup("Hello World!!!!");
    }
    ~tempNode() {
    }

    const char *srMap;
};

int main()
{
    struct tempNode *pTT = new tempNode();
    std::string sr_map = pTT->srMap;
    cout << "sr_map:\t" << sr_map.c_str() << endl;
    cout << "tt.srMap:\t" << pTT->srMap << endl;
    delete (pTT);
    cout << "sr_map:\t" << sr_map.c_str() << endl;
    // cout << "tt.srMap:\t" << pTT->srMap << endl;
    return 0;

}