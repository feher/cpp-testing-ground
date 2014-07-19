#include "../rpc_shared/remote_functions.hpp"
#include "rpc_wrapper.hpp"

#include <iostream>

// TODO: Update this if you add/remove RPC functions.
//       Add/remove a corresponding RPC_WRAPPER_HANDLE_*() line.
std::vector<uint8_t> rpc_wrapper::HandleRequest(const char *pSignature, const std::vector<uint8_t> &ArgData)
{
    auto Signature = std::string{pSignature};
    RPC_WRAPPER_HANDLE_VOID_REQUEST(RemoteFunction1, Signature, ArgData);
    RPC_WRAPPER_HANDLE_REQUEST(RemoteFunction2, Signature, ArgData);
    RPC_WRAPPER_HANDLE_REQUEST(RemoteFunction3, Signature, ArgData);
    return{};
}

void RemoteFunction1(const std::vector<double> &, const char *)
{
    // TODO: Provide implementation.
    std::cout << __FUNCTION__ << std::endl;
}

std::vector<std::string> RemoteFunction2(const std::string &, double)
{
    // TODO: Provide implementation.
    std::cout << __FUNCTION__ << std::endl;
    return std::vector<std::string>{};
}

std::string RemoteFunction3(const std::unordered_map<std::string, std::vector<float>> &, const short *)
{
    // TODO: Provide implementation.
    std::cout << __FUNCTION__ << std::endl;
    return std::string{};
}

