#include "../rpc_shared/remote_functions.hpp"

#include <string>
#include <iostream>

int main()
{
    auto DoubleVector = std::vector<double>{};
    auto pCharPointer = "Hello";

    std::cout << "\nTest 1" << std::endl;
    RemoteFunction1(DoubleVector, pCharPointer);

    std::cout << "\nTest 2" << std::endl;
    const auto &StringVector = RemoteFunction2(DoubleVector, pCharPointer);

    std::cout << "\nTest 3" << std::endl;
    const auto &String = RemoteFunction3(DoubleVector, pCharPointer);

    return 0;
}
