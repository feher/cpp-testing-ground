#include "header1.hpp"

#include <string>
#include <iostream>

int main()
{
    auto DoubleVector = std::vector<double>{};
    auto pCharPointer = "Hello";

    RemoteFunction(DoubleVector, pCharPointer);

    return 0;
}
