#include "boost/format.hpp"

#include <iostream>

namespace tsprint
{
    class Print
    {
    public:
        template<typename T>
        Print& operator()(T&& Arg)
        {
            std::cout << Arg;
            return *this;
        }
    };
}

int main()
{
    auto a = 1;
    auto b = "hi";
    auto c = std::string{"oi"};
    tsprint::Print{}(a)(b)(c)('\n');
}
