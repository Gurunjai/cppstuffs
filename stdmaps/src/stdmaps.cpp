#include <iostream>
#include <map>
#include <tuple>
#include <cassert>

using namespace std;
typedef struct _stats_obj {
    uint32_t a;
    char b;
    std::string c;
    uint32_t d;
    int x;
    int y;
    int z;
    int w;
} stats_obj;

using keyInfo = tuple<uint32_t, char, std::string, uint32_t>;
using statsMap = map<keyInfo, stats_obj>;

statsMap sObj;

void dump()
{
    for (auto it = sObj.begin(); it != sObj.end(); it++) {
        auto [code, service, sMap, arl] = it->first;
        cout << "[" << code << ", " << service << ", " << sMap << ", " << arl << "]: ";
        auto obj = it->second;
        assert(code == obj.a);
        assert(service == obj.b);
        assert(sMap == obj.c);
        assert(arl == obj.d);
        cout << obj.x << ":" << obj.y << ":" << obj.z << ":" << obj.w << ";" << endl;
    }
}

keyInfo MakeKeyInfo(uint32_t code, char serv, std::string sMap, uint32_t arl)
{
    return keyInfo{code, serv, sMap, arl};
}

void push(stats_obj &obj)
{
    auto keyIdx = MakeKeyInfo(obj.a, obj.b, obj.c, obj.d);
    sObj[keyIdx] = obj;
}

int main(void)
{
    stats_obj s1{10, 'S', "map-1", 1, 10, 20, 30, 40};
    stats_obj s2{90, 'W', "map-ff", 3, 90, 80, 70, 60};
    stats_obj s3{10, 'S', "map-1", 1, 100, 200, 300, 400};

    push(s1);
    push(s2);
    push(s3);

    dump();

    return 0;
}