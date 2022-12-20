#include <iostream>

using namespace std;

typedef struct {
    int count;
}SwapData;

typedef struct {
    struct {
        uint32_t rollback_fix : 1;
        uint32_t pad : 31;
    }flags;
}ConfigMdt;

typedef struct {
    struct {
        uint32_t rollback_fix : 1;
        uint32_t pad : 31;
    }flags;
}StoreConfig;

class LMeta {
    public:
    LMeta() { init(); }
    ~LMeta() {}

    void init() {
        memset(&m_cfgTags, 0, sizeof(ConfigMdt));
    }

    ConfigMdt &config() {
        return m_cfgTags;
    }

    private:
    ConfigMdt m_cfgTags;
};

class MMeta {
    public:
    MMeta() { init(); }
    ~MMeta() {}

    void init() {
        memset(&m_cfgTags, 0, sizeof(StoreConfig));
    }

    auto &config() {
        return m_cfgTags;
    }

    void Set() {
        m_cfgTags.flags.rollback_fix ^= 1;
    }

    private:
    StoreConfig m_cfgTags;
};

class Global {
    public:
    Global()
        : lmeta(new LMeta)
        , mmeta(new MMeta)
    {
    }

    ~Global() {

    }

    decltype(auto) GetConfig(LMeta* lm) {
        return lm->config();
    }

    decltype(auto) GetConfig(MMeta* mm) {
        return mm->config();
    }

    auto GetLMeta() { return lmeta.get(); }
    auto GetMMeta() { return mmeta.get(); }

    public:
    unique_ptr<LMeta>  lmeta;
    unique_ptr<MMeta>  mmeta;
};

int main(void) {
    Global global;

    global.GetConfig(global.lmeta.get());
    return 0;
}