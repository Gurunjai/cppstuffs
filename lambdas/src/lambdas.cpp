#include <iostream>

using namespace std;

int global = 10;

struct Baz {
    void sFoo() {
        const auto lam = [this ]() { cout << s <<endl; };
        lam();
    }

    std::string s = "Hello Lambdas";
};

int main()
{
    static int sInt = 15;
    cout << "Global \t Static " << endl;
    auto print = []() { cout << "  " << global << " \t   " << sInt << endl;};
    print();
    auto foo = [= ] () mutable noexcept { ++global; ++sInt; };
    foo();
    print();
    const auto increaseGlobal = []() noexcept { ++global; ++sInt; };
    increaseGlobal();
    print();
    const auto moreIncreaseGlobal = [&]() noexcept { ++global; ++sInt; };
    moreIncreaseGlobal();
    print();
    const auto byValueIncrease = [=]() noexcept { ++global; ++sInt; };
    byValueIncrease();
    print();
    /*
        ./src/charptr.cpp:24:41: error: 
            'global' cannot be captured because it does not have automatic storage duration
        ./src/charptr.cpp:24:49: error: 
            'sInt' cannot be captured because it does not have automatic storage duration
        const auto directCaptureIncrease = [global, sInt]() noexcept { ++global; ++sInt; };
        directCaptureIncrease();
        print();
    */

    Baz b;
    b.sFoo();
    return 0;
}