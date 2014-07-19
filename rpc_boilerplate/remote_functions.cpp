#include "../rpc_shared/remote_functions.hpp"
#include "rpc_wrapper.hpp"

void RemoteFunction1(const std::vector<double> &DoubleVector, const char *pCharPointer)
{
    auto RpcWrapper = rpc_wrapper::MakeVoidWrapper(__FUNCTION__, DoubleVector, pCharPointer);
    RpcWrapper.Execute();
}

std::vector<std::string> RemoteFunction2(const std::string &String, double Double)
{
    auto RpcWrapper = rpc_wrapper::MakeWrapper(__FUNCTION__, std::vector<std::string>{}, String, Double);
    return RpcWrapper.Execute();
}

std::string RemoteFunction3(const std::unordered_map<std::string, std::vector<float>> &FloatVectorMap, const short *pShortArray)
{
    auto RpcWrapper = rpc_wrapper::MakeWrapper(__FUNCTION__, std::string{}, FloatVectorMap, pShortArray);
    return RpcWrapper.Execute();
}

