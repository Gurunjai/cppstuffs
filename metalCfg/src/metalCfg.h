#include <iostream>
#include <unordered_map>
using namespace std;

typedef struct {
    int count;
}SwapData;

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

class AInterface {
    public:
    virtual void init() = 0;
};

class ABase : public AInterface {
    friend class LMeta;
    friend class MMeta;

    public:
    typedef enum {
        LEGACY = 0,
        METAL,

        UNKNOWN,
    }Type;

    ABase();
    virtual ~ABase(); 

    template<typename T>
    T* GetMtd();

    void init();

    Type getIndex(bool isMetal = false);

    decltype(auto) GetMetadata(bool isMetal = false) noexcept;

    decltype(auto) GetPairMtd(bool isMetal = false) noexcept;
    
    decltype(auto) GetPair(bool isMetal = false) noexcept;

    decltype(auto) GetMtdPair(bool isMetal = false) noexcept;

    decltype(auto) GetLMeta();

    decltype(auto) GetMMeta();

    decltype(auto) GetPtr(ABase::Type t) noexcept;

    inline SwapData& cacheSwap() {
        return m_swapData;
    }

    inline int getConfigSwapCount() {
        return m_swapData.count;
    }

    public:
    SwapData m_swapData;

    private:
    unique_ptr<ABase> m_aObj[UNKNOWN];
};

class LMeta : public ABase {
    public:
    LMeta() : ABase() {
        init();
    }
    ~LMeta() {}

    void init();

    inline ConfigMdt &config() {
        return m_cfgTags;
    }

    inline void Set(std::string t) {
        config().sTest = t;
    }

    private:
    ConfigMdt m_cfgTags;
};

class MMeta : public ABase {
    public:
    MMeta() : ABase() { init(); }
    ~MMeta() {}
    void init();

    inline auto &config() {
        return m_cfgTags;
    }

    void Set();

    private:
    StoreConfig m_cfgTags;
};