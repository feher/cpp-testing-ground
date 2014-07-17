#pragma once

#include "../rpc_shared/rpc_serialize.hpp"
#include "apply_tuple.hpp"

#include <tuple>
#include <vector>
#include <iostream> // for debug prints
#include <cstdint> // uint8_t

#define RPC_WRAPPER_HANDLE_REQUEST(FunctionName, Signature, ArgData) \
    do \
    { \
        /* TODO: Change this if you want to dispatch based on the whole signature. */ \
        if((Signature).find(#FunctionName "|") == 0) \
        { \
            const auto &Arguments = \
                rpc_wrapper::DeserializeArguments<FunctionName ## __ARG_TYPES>(ArgData); \
            const auto &TempResult = apply_tuple::apply_tuple(FunctionName, Arguments); \
            return rpc_serialize::Serialize(TempResult); \
        } \
    } while (false)

#define RPC_WRAPPER_HANDLE_VOID_REQUEST(FunctionName, Signature, ArgData) \
    do \
    { \
        /* TODO: Change this if you want to dispatch based on the whole signature. */ \
        if((Signature).find(#FunctionName "|") == 0) \
        { \
            const auto &Arguments = \
                rpc_wrapper::DeserializeArguments<FunctionName ## __ARG_TYPES>(ArgData); \
            apply_tuple::apply_tuple(FunctionName, Arguments); \
            return std::vector<uint8_t>{}; \
        } \
    } while (false)

namespace rpc_wrapper
{
    template <typename TTuple, std::size_t ArgIndex>
    struct DeserializeArgs_c
    {
        static void Do(TTuple &Result, const std::vector<uint8_t> &ArgData, std::size_t ArgDataOffset)
        {
            static const auto TupleSize = std::tuple_size<TTuple>::value;
            auto &Arg = std::get<TupleSize - ArgIndex>(Result);
            ArgDataOffset += rpc_serialize::Deserialize(Arg, ArgData, ArgDataOffset);
            rpc_wrapper::DeserializeArgs_c<TTuple, ArgIndex - 1>::Do(Result, ArgData, ArgDataOffset);
        }
    };

    template <typename TTuple>
    struct DeserializeArgs_c<TTuple, 0>
    {
        static void Do(TTuple &, const std::vector<uint8_t> &, std::size_t)
        {
            // Nothing.
        }
    };

    template <typename ...T>
    std::tuple<T...> DeserializeArguments(const std::vector<uint8_t> &ArgData)
    {
        auto Result = std::tuple<T...>{};
        DeserializeArgs_c<decltype(Result), sizeof...(T)>::Do(Result, ArgData, 0);
        return Result;
    }

    std::vector<uint8_t> HandleRequest(const char *pSignature, const std::vector<uint8_t> &ArgData);

    void SendReply(const std::vector<uint8_t> &Result);
}