#include <iostream>
#include <cassert>

using namespace std;

class Foo;
class Bar;

typedef struct {
    struct {
        uint32_t rollback_fix : 1;
        uint32_t pad : 31;
    }flags;
    std::string sTest;
}ConfigMdt;

typedef struct {
    struct {
        uint32_t rollback_fix : 1;
        uint32_t pad : 31;
    }flags;
}StoreConfig;

class Mtd;
class Metal;

class Global {
    public:
    unique_ptr<Mtd> mtd;
    unique_ptr<Metal> metal;

    Global();

    ~Global() {}
};
Global global;

class Mtd {
    public:
        Mtd() {
            memset(&cfg, 0, sizeof(ConfigMdt));
        }

        const ConfigMdt& config() const { return cfg; }

        void updateConfigMtd();

    private:
        ConfigMdt cfg;
};

class Metal {
    public:
        Metal(){
            memset(&cfg, 0, sizeof(StoreConfig));
        }
        
        void updateMe();
        const StoreConfig& config() const { return cfg; }
    private:
        StoreConfig cfg;
};


void Metal::updateMe()
{
    assert(global.metal.get() == this);
    cfg.flags.rollback_fix ^= 1;
    global.mtd->updateConfigMtd();
}

void Mtd::updateConfigMtd() {
    cfg.flags.rollback_fix = global.metal->config().flags.rollback_fix;
}

inline Global::Global()
    : mtd(new Mtd)
    , metal(new Metal)
{
    ;
}

int main()
{
    cout << "Initial Values:" << endl;
    cout << "\tMtd Rollback Flag:\t" << global.mtd->config().flags.rollback_fix << endl;
    cout << "\tMetal Rollback Flag:\t" << global.metal->config().flags.rollback_fix << endl;
    global.metal->updateMe();
    cout << "Updated Values:" << endl;
    cout << "\tMtd Rollback Flag:\t" << global.mtd->config().flags.rollback_fix << endl;
    cout << "\tMetal Rollback Flag:\t" << global.metal->config().flags.rollback_fix << endl;
    global.metal->updateMe();
    cout << "Cleared Values:" << endl;
    cout << "\tMtd Rollback Flag:\t" << global.mtd->config().flags.rollback_fix << endl;
    cout << "\tMetal Rollback Flag:\t" << global.metal->config().flags.rollback_fix << endl;

    const char *p1 = "test";
    std::string p2 = "test";
    assert(p1 != p2);
    return 0;
}