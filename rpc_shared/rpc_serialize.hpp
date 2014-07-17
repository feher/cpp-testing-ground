#pragma once

#include <vector>
#include <string>
#include <cstdint> // uint8_t

namespace rpc_serialize
{
    // TODO: Add here the serialization functions for your supported types.
    std::vector<uint8_t> Serialize(const std::vector<double> &);
    std::vector<uint8_t> Serialize(const char *);
    std::vector<uint8_t> Serialize(const std::vector<std::string> &);
    std::vector<uint8_t> Serialize(const std::string &);

    // TODO: Add here the de-serialization functions for your supported types.
    // Return the amount of bytes consumed from Data!
    std::size_t Deserialize(std::vector<std::string> &Result, const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
    std::size_t Deserialize(std::string &Result, const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
    std::size_t Deserialize(std::vector<double> &Result, const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
    std::size_t Deserialize(const char * &Result, const std::vector<uint8_t> &, std::size_t);
}
