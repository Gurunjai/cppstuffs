#include "twoObj.h"
#include <cassert>

using namespace std;

goc::configuration::StoreMetadata& goc::configuration::StoreMetadata::operator=(metal::MetalMetadata& mmdt)
{
    m_cfgtags.flags.rollback_fix = mmdt.config().flags.rollback_fix;
    m_cfgtags.cacheSwapDir = mmdt.config().cacheSwapDir;
    return *this;
}

#define READCONFIG(X) (metal::isMetal() ? global.mmdt->getConfigMdt().config.X : global.smdt->m_cfgtags.X)
#define IS_FLAG_SET(F) (F & 0x1)
#define FLAG_IT(cond) (gMetal = cond)
#define PRINT_IT(X) \
    FLAG_IT(true); \
    cout << "Metal Flag Value is: " << IS_FLAG_SET(READCONFIG(X)) << endl; \
    FLAG_IT(false); \
    cout << "Non-Metal Flag Value is: " << IS_FLAG_SET(READCONFIG(X)) << endl << endl; \

#define TEST(X, V) \
    V ^= 0x1; \
    PRINT_IT(X); \
    V ^= 0x1;

int main() {
    Global global;

    cout << READCONFIG(flags.rollback_fix) <<endl;
    TEST(flags.rollback_fix, global.mmdt->m_cfgtags.config.flags.rollback_fix);
    TEST(flags.rollback_fix, global.smdt->m_cfgtags.flags.rollback_fix);
    
    PRINT_IT(flags.rollback_fix)

    auto cfg = global.mmdt->config();
    cfg.flags.rollback_fix |= 0x1;
    cout << "Metadata Config Output: " << global.mmdt->config().flags.rollback_fix << endl;
    cfg.flags.rollback_fix &= 0x0;
    cout << "Metadata Config Output: " << global.mmdt->config().flags.rollback_fix << endl;

    goc::configuration::StoreMetadata mtd = *global.smdt.get();
    metal::MetalMetadata mmtd = *global.mmdt.get();

    assert(mtd == mmtd);
    mtd = mmtd;

    mtd.m_cfgtags = mmtd.config();

    return 0;
}