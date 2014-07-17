#pragma once

#include "../rpc_shared/rpc_serialize.hpp"

#include <utility> // pair
#include <string>
#include <vector>
#include <cstdint> // uint8_t
#include <iostream> // for debug prints

namespace rpc_wrapper
{
    std::vector<uint8_t> SendRequestAndGetReply(
        const std::string &Signature,
        const std::vector<uint8_t> &SerializedArguments)
    {
        // TODO: Do the RPC call. The return value is probably a bunch of bytes.
        std::cout << __FUNCTION__ << " : " << Signature << std::endl;
        return std::vector<uint8_t>{};
    }

    template <typename T>
    void SerializeArg(std::vector<std::vector<uint8_t>> &SerializedArgs, const T &Arg)
    {
        SerializedArgs.push_back(rpc_serialize::Serialize(Arg));
    }

    template <typename THead, typename ...TRest>
    void SerializeArg(std::vector<std::vector<uint8_t>> &SerializedArgs, const THead &Head, const TRest &...Rest)
    {
        SerializeArg(SerializedArgs, Head);
        SerializeArg(SerializedArgs, Rest...);
    }

    template <typename ...TArgs>
    std::vector<std::vector<uint8_t>> SerializeArguments(const TArgs &...Args)
    {
        auto Result = std::vector<std::vector<uint8_t>>{};
        SerializeArg(Result, Args...);
        return Result;
    }

    std::vector<uint8_t> FlattenSerializedArguments(const std::vector<std::vector<uint8_t>> &SerializedArguments)
    {
        // TODO: Concatenate the items from SerializedArguments using some kind of separator byte sequence.
        (void)SerializedArguments;
        return std::vector<uint8_t>{};
    }

    void BuildSig(std::string &Signature, const std::vector<double> &)
    {
        std::cout << __FUNCTION__ << " : std::vector<double> " << std::endl;
        Signature.append("|std::vector<double>");
    }

    void BuildSig(std::string &Signature, const char *)
    {
        std::cout << __FUNCTION__ << " : char * " << std::endl;
        Signature.append("|char *");
    }

    template <typename THead, typename ...TRest>
    void BuildSig(std::string &Signature, const THead &Head, const TRest &...Rest)
    {
        BuildSig(Signature, Head);
        BuildSig(Signature, Rest...);
    }

    template <typename ...TArgs>
    std::string BuildSignature(const TArgs &...Args)
    {
        auto Result = std::string{};
        BuildSig(Result, Args...);
        return Result;
    }

    template <typename TRet, typename ...TArgs>
    class RpcWrapper_c
    {
    public:
        RpcWrapper_c(const char *pFunctionName, const TArgs &...Args)
            : m_Signature{}
        {
            m_Signature = std::string{pFunctionName};
            m_Signature.append(rpc_wrapper::BuildSignature(Args...));
            m_SerializedArguments =
                rpc_wrapper::FlattenSerializedArguments(
                rpc_wrapper::SerializeArguments(Args...));
        }
        TRet Execute()
        {
            auto VoidResult = rpc_wrapper::SendRequestAndGetReply(m_Signature, m_SerializedArguments);
            auto TypedResult = TRet{};
            rpc_serialize::Deserialize(TypedResult, VoidResult, 0);
            return TypedResult;
        }
    private:
        std::string m_Signature;
        std::vector<uint8_t> m_SerializedArguments;

    };

    template <typename ...TArgs>
    class RpcWrapper_c<void, TArgs...>
    {
    public:
        RpcWrapper_c(const char *pFunctionName, const TArgs &...Args)
            : m_Signature{}
        {
            m_Signature = std::string{pFunctionName};
            m_Signature.append(":").append(rpc_wrapper::BuildSignature(Args...));
            m_SerializedArguments =
                rpc_wrapper::FlattenSerializedArguments(
                rpc_wrapper::SerializeArguments(Args...));
        }
        void Execute()
        {
            auto VoidResult = rpc_wrapper::SendRequestAndGetReply(m_Signature, m_SerializedArguments);
            (void)VoidResult; // We just throw this away.
        }
    private:
        std::string m_Signature;
        std::vector<uint8_t> m_SerializedArguments;
    };


    template <typename ...TArgs>
    RpcWrapper_c<void, TArgs...> MakeVoidWrapper(const char *pFunctionName, const TArgs &...Args)
    {
        return RpcWrapper_c<void, TArgs...>{pFunctionName, Args...};
    }

    template <typename TRet, typename ...TArgs>
    RpcWrapper_c<TRet, TArgs...> MakeWrapper(const char *pFunctionName, const TRet &, const TArgs &...Args)
    {
        return RpcWrapper_c<TRet, TArgs...>{pFunctionName, Args...};
    }
}
