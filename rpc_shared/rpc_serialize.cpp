#include "rpc_serialize.hpp"

#include <iostream> // for debug prints

std::vector<uint8_t> rpc_serialize::Serialize(const std::vector<double> &)
{
    // TODO: Serialize from std::vector<double> to std::vector<uint8_t>.
    std::cout << __FUNCTION__ << " <- std::vector<double>" << std::endl;
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> rpc_serialize::Serialize(const char *)
{
    // TODO: Serialize from char* to std::vector<uint8_t>.
    std::cout << __FUNCTION__ << " <- char * " << std::endl;
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> rpc_serialize::Serialize(const std::vector<std::string> &)
{
    // TODO: Serialize.
    std::cout << __FUNCTION__ << " <- std::vector<std::string> " << std::endl;
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> rpc_serialize::Serialize(const std::string &)
{
    // TODO: Serialize.
    std::cout << __FUNCTION__ << " <- std::string " << std::endl;
    return std::vector<uint8_t>{};
}

std::size_t rpc_serialize::Deserialize(std::vector<std::string> &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize from byte array to std::vector<std::string>.
    std::cout << __FUNCTION__ << " -> std::vector<std::string> " << std::endl;
    Result = std::vector<std::string>{};
    return 0;
}

std::size_t rpc_serialize::Deserialize(std::string &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize from byte array to std::string.
    std::cout << __FUNCTION__ << " -> std::string " << std::endl;
    Result = std::string{};
    return 0;
}

std::size_t rpc_serialize::Deserialize(std::vector<double> &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize from byte array to std::vector<std::double>.
    std::cout << __FUNCTION__ << " -> std::vector<double> " << std::endl;
    Result = std::vector<double>{};
    return 0;
}

std::size_t rpc_serialize::Deserialize(const char * &Result, const std::vector<uint8_t> &, std::size_t)
{
    // TODO: De-serialize from byte array to char*.
    std::cout << __FUNCTION__ << " -> char * " << std::endl;
    Result = "hello";
    return 0;
}
