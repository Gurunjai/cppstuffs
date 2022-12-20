#include <type_traits>
#include <iostream>

// enum class enabler_t {};

// template<typename T>
// using EnableIf = typename std::enable_if<T::value, enabler_t>::type;

// template<class T, EnableIf<std::is_integral<T>>...>
// auto function(T t) {
//     std::cout << "integral" << std::endl;
//     return;
// }

// template<class T, EnableIf<std::is_floating_point<T>>...>
// auto function(T t) {
//     std::cout << "floating point" << std::endl;
//     return;
// }

// int main()
// {
//     function(0);
//     function(0.0f);
//     // std::cout << std::boolalpha << std::is_integral<decltype(ret)>::value << std::endl;
//     // std::cout << std::is_floating_point<decltype(ret2)>::value << std::endl;
//     return 0;
// }

enum class IntWrapper{};
template<class T>
struct IsMyInt
    : std::is_integral<T>
    {

    };

template<>
struct IsMyInt<IntWrapper>
    : std::true_type
{

};

int main() {
    static_assert(IsMyInt<IntWrapper>::value, "Invalid type.");
    return 0;
}

