#include "rpc_serialize.hpp"

#include <iostream> // for debug prints

std::string rpc_serialize::Signature(const double)
{
    const auto &Result = std::string{"double"};
    std::cout << __FUNCTION__ << " : " << Result << std::endl;
    return Result;
}

std::string rpc_serialize::Signature(const char *)
{
    const auto &Result = std::string{"char *"};
    std::cout << __FUNCTION__ << " : " << Result << std::endl;
    return Result;
}

std::string rpc_serialize::Signature(const short *)
{
    const auto &Result = std::string{"short *"};
    std::cout << __FUNCTION__ << " : " << Result << std::endl;
    return Result;
}

std::string rpc_serialize::Signature(const std::string &)
{
    const auto &Result = std::string{"std::string"};
    std::cout << __FUNCTION__ << " : " << Result << std::endl;
    return Result;
}

std::string rpc_serialize::Signature(const std::vector<double> &)
{
    const auto &Result = std::string{"std::vector<double>"};
    std::cout << __FUNCTION__ << " : " << Result << std::endl;
    return Result;
}

std::string rpc_serialize::Signature(const std::unordered_map<std::string, std::vector<float>> &)
{
    const auto &Result = std::string{"std::unordered_map<std::string, std::vector<float>>"};
    std::cout << __FUNCTION__ << " : " << Result << std::endl;
    return Result;
}

std::vector<uint8_t> rpc_serialize::Serialize(const double &)
{
    // TODO: Serialize.
    std::cout << __FUNCTION__ << " <- double " << std::endl;
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> rpc_serialize::Serialize(const char *)
{
    // TODO: Serialize.
    std::cout << __FUNCTION__ << " <- char * " << std::endl;
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> rpc_serialize::Serialize(const short *)
{
    // TODO: Serialize.
    std::cout << __FUNCTION__ << " <- short * " << std::endl;
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> rpc_serialize::Serialize(const std::string &)
{
    // TODO: Serialize.
    std::cout << __FUNCTION__ << " <- std::string " << std::endl;
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> rpc_serialize::Serialize(const std::vector<double> &)
{
    // TODO: Serialize.
    std::cout << __FUNCTION__ << " <- std::vector<double>" << std::endl;
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> rpc_serialize::Serialize(const std::vector<std::string> &)
{
    // TODO: Serialize.
    std::cout << __FUNCTION__ << " <- std::vector<std::string> " << std::endl;
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> rpc_serialize::Serialize(const std::unordered_map<std::string, std::vector<float>> &)
{
    // TODO: Serialize.
    std::cout << __FUNCTION__ << " <- std::unordered_map<std::string, std::vector<float>> " << std::endl;
    return std::vector<uint8_t>{};
}

std::size_t rpc_serialize::Deserialize(double &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize.
    std::cout << __FUNCTION__ << " -> double " << std::endl;
    return 0;
}

std::size_t rpc_serialize::Deserialize(const char * &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize.
    std::cout << __FUNCTION__ << " -> char * " << std::endl;
    Result = "hello";
    return 0;
}

std::size_t rpc_serialize::Deserialize(const short * &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize.
    std::cout << __FUNCTION__ << " -> short * " << std::endl;
    return 0;
}

std::size_t rpc_serialize::Deserialize(std::string &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize.
    std::cout << __FUNCTION__ << " -> std::string " << std::endl;
    Result = std::string{};
    return 0;
}

std::size_t rpc_serialize::Deserialize(std::vector<double> &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize.
    std::cout << __FUNCTION__ << " -> std::vector<double> " << std::endl;
    Result = std::vector<double>{};
    return 0;
}

std::size_t rpc_serialize::Deserialize(std::vector<std::string> &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize.
    std::cout << __FUNCTION__ << " -> std::vector<std::string> " << std::endl;
    Result = std::vector<std::string>{};
    return 0;
}

std::size_t rpc_serialize::Deserialize(
    std::unordered_map<std::string, std::vector<float>> &Result,
    const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset)
{
    // TODO: De-serialize.
    std::cout << __FUNCTION__ << " -> std::unordered_map<std::string, std::vector<float>> " << std::endl;
    Result = std::unordered_map<std::string, std::vector<float>>{};
    return 0;
}
