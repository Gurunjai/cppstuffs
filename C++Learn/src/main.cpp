#include <iostream>

/*
hw.memsize: 17179869184
hw.activecpu: 10
hw.pagesize: 16384
hw.pagesize32: 16384
hw.cachelinesize: 128
hw.l1icachesize: 131072
hw.l1dcachesize: 65536
hw.l2cachesize: 4194304
*/

#define L1CacheSize 65536

constexpr auto kL1CacheCapacity = L1CacheSize;
constexpr auto kSize = kL1CacheCapacity / sizeof(int);
using MatrixType = std::array<std::array<int, kSize>, kSize>;
auto cache_thrashing(MatrixType& matrix)
{
    auto counter = 0;
    for (auto i = 0; i < kSize; ++i) {
        for (auto j = 0; j < kSize; ++j) {
            matrix[i][j] = counter++;
        }
    }
}

int main(void)
{

    MatrixType mat;
    cache_thrashing(mat);
    return 0;
}