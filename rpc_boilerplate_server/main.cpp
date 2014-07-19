#include "../rpc_shared/remote_functions.hpp"
#include "rpc_wrapper.hpp"

#include <iostream>

int main()
{
    auto DoubleVector = std::vector < double > {};
    auto pCharPointer = "Hello";

    // Direct function calls.

    RemoteFunction1(DoubleVector, pCharPointer);
    const auto &StringVector = RemoteFunction2(std::string{"test server call"}, 2.2);
    const auto &String = RemoteFunction3(std::unordered_map<std::string, std::vector<float>>{}, static_cast<short*>(nullptr));

    // Handle remote function calls.

    std::cout << "\nTest 1" << std::endl;
    {
        // TODO: Get the data from the client.
        auto *pClientSignature = "RemoteFunction1|std::vector<double>|char *";
        auto ClientArguments = std::vector<uint8_t>{};
        const auto &Result = rpc_wrapper::HandleRequest(pClientSignature, ClientArguments);
        rpc_wrapper::SendReply(Result);
    }

    std::cout << "\nTest 2" << std::endl;
    {
        // TODO: Get the data from the client.
        auto *pClientSignature = "RemoteFunction2|std::vector<double>|char *";
        auto ClientArguments = std::vector<uint8_t>{};
        const auto &Result = rpc_wrapper::HandleRequest(pClientSignature, ClientArguments);
        rpc_wrapper::SendReply(Result);
    }

    std::cout << "\nTest 3" << std::endl;
    {
        // TODO: Get the data from the client.
        auto *pClientSignature = "RemoteFunction3|std::unordered_map<std::string, std::vector<float>>|short *";
        auto ClientArguments = std::vector<uint8_t>{};
        const auto &Result = rpc_wrapper::HandleRequest(pClientSignature, ClientArguments);
        rpc_wrapper::SendReply(Result);
    }

    return 0;
}
