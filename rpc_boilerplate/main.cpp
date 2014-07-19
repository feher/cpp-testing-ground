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
    const auto &StringVector = RemoteFunction2(std::string{"test"}, 1.1);

    std::cout << "\nTest 3" << std::endl;
    const auto &String = RemoteFunction3(std::unordered_map<std::string, std::vector<float>>{}, static_cast<short*>(nullptr));

    return 0;
}
