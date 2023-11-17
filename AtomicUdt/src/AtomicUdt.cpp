#include <iostream>
#include <atomic>

using namespace std;

struct sr_conf
{
    int a;
    int b;
    int c;
    int d;

    bool operator==(sr_conf &rhs)
    {
        return (memcmp(this, &rhs, sizeof(rhs)) == 0);
    }

    bool operator!=(sr_conf &rhs)
    {
        return !(*this == rhs);
    }

    void dump() {
        cout << "A= " << a << ", B= " << b << ", C= " << c << ", D= " << d << endl;
    }
};

static constexpr int PERSISTED = 0;
static constexpr int ACTIVE = 1;

int main(void) 
{
    sr_conf s1{1, 2, 3, 4};
    sr_conf s2{9, 8, 7, 6};
    atomic<sr_conf> aSr[2];
    aSr[PERSISTED] = s1;
    aSr[ACTIVE] = s2;
    cout << "PERSISTED: ";
    aSr[PERSISTED].load().dump();
    cout << "ACTIVE: ";
    aSr[ACTIVE].load().dump();
    // aSr[PERSISTED].compare_exchange_weak((aSr[PERSISTED].load()), (aSr[ACTIVE].load()));
    return 0;
}