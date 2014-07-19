#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint> // uint8_t

namespace rpc_serialize
{
    // TODO: Add here the signature generator functions for your supported types.
    std::string Signature(const double);
    std::string Signature(const char *);
    std::string Signature(const short *);
    std::string Signature(const std::string &);
    std::string Signature(const std::vector<double> &);
    std::string Signature(const std::unordered_map<std::string, std::vector<float>> &);

    // TODO: Add here the serialization functions for your supported types.
    std::vector<uint8_t> Serialize(const double &);
    std::vector<uint8_t> Serialize(const char *);
    std::vector<uint8_t> Serialize(const short *);
    std::vector<uint8_t> Serialize(const std::string &);
    std::vector<uint8_t> Serialize(const std::vector<double> &);
    std::vector<uint8_t> Serialize(const std::vector<std::string> &);
    std::vector<uint8_t> Serialize(const std::unordered_map<std::string, std::vector<float>> &);

    // TODO: Add here the de-serialization functions for your supported types.
    // @param[out] Result         The de-serialized data.
    // @param[in]  ArgData        The container of the serialized data.
    // @param[in]  ArgDataOffset  Start de-serializing the data from ArgData[ArgDataOffset].
    // @return The amount of bytes consumed starting from ArgData[ArgDataOffset].
    std::size_t Deserialize(double &Result,
                            const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
    std::size_t Deserialize(const char * &Result,
                            const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
    std::size_t Deserialize(const short * &Result, 
                            const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
    std::size_t Deserialize(std::vector<std::string> &Result, 
                            const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
    std::size_t Deserialize(std::string &Result, 
                            const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
    std::size_t Deserialize(std::vector<double> &Result, 
                            const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
    std::size_t Deserialize(std::unordered_map<std::string, std::vector<float>> &Result, 
                            const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset);
}
