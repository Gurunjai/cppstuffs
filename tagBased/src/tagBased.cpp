#include <iostream>

struct OpenTag {};
struct HighTag {};
struct LowTag {};
struct CloseTag {};
struct Ema100Tag {};

struct Tick {

    template <typename Tag> struct Member {
        double val;

        operator double () const { return val; }

        operator double& () { return val; }
    };

    struct AllMembers : Member<OpenTag>,
                        Member<HighTag>,
                        Member<LowTag>,
                        Member<CloseTag>,
                        Member<Ema100Tag> {};
    
    AllMembers data;

    template <typename Tag>
    double operator[](Tag t) const {
        return (Member<Tag> const&)(data);
    }

    template <typename Tag>
    double& operator[](Tag t) {
        return (Member<Tag>&)(data);
    }
};

int main()
{
    Tick t;
    t[OpenTag()] = 12.345;
    std::cout << t[OpenTag()] << std::endl;
    return 0;
}