#include <iostream>
#include <string>
#include <memory>
bool gMetal = false;

namespace metal {
    class store_config
    {
        public:
        struct {
            struct {
                uint32_t rollback_fix : 1;
                uint32_t pad: 31;
            }flags{0};

            std::string cacheSwapDir;
        } config;
    };

    class MetalMetadata final {
        public:
        MetalMetadata() = default;
        ~MetalMetadata() = default;

        store_config m_cfgtags;

        inline store_config &getConfigMdt() { return m_cfgtags; }

        inline auto config() {
            return m_cfgtags.config;
        }
    };

    bool isMetal() { return gMetal; }
} // namespace metal

namespace goc
{
namespace configuration
{
    struct ConfigMdt{
        struct {
            uint32_t rollback_fix : 1;
            uint32_t pad: 31;
        } flags{1, 0};

        ConfigMdt &operator=(const metal::store_config &sc) {
            flags.rollback_fix = sc.config.flags.rollback_fix;
            return *this;
        }

        bool test_fix_mdt;
        std::string cacheSwapDir;
    };

    class StoreMetadata final {
        public:
        StoreMetadata() = default;
        ~StoreMetadata() = default;

        StoreMetadata& operator=(metal::MetalMetadata &mmtd);

        bool operator==(metal::MetalMetadata& mmdt)
        {
            std::cout << "Smdt:\t" << this->getConfigMdt().flags.rollback_fix <<", Mmdt:\t" << mmdt.config().flags.rollback_fix << std::endl;
            if (this->getConfigMdt().flags.rollback_fix != mmdt.config().flags.rollback_fix)
                return false;
            if (this->getConfigMdt().cacheSwapDir != mmdt.config().cacheSwapDir)
                return false;
    
            return true;
        }

        const ConfigMdt &getConfigMdt() const { return m_cfgtags; }

        ConfigMdt m_cfgtags;
    };

} // namespace configuration
} // namespace goc

class Global
{
    public:
    std::unique_ptr<goc::configuration::StoreMetadata> smdt;
    std::unique_ptr<metal::MetalMetadata> mmdt;

    Global()
        : smdt(new goc::configuration::StoreMetadata)
        , mmdt(new metal::MetalMetadata) {

    }

    ~Global() = default;

    // template<typename T>
    auto &GetMetadata() {
        return mmdt;
    }
};