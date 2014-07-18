#pragma once

#include "../rpc_shared/rpc_serialize.hpp"

#include <utility> // pair
#include <string>
#include <vector>
#include <cstdint> // uint8_t
#include <iostream> // for debug prints

namespace rpc_wrapper
{
    namespace helper
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
            rpc_wrapper::helper::SerializeArg(SerializedArgs, Head);
            rpc_wrapper::helper::SerializeArg(SerializedArgs, Rest...);
        }

        template <typename ...TArgs>
        std::vector<std::vector<uint8_t>> SerializeArguments(const TArgs &...Args)
        {
            auto Result = std::vector<std::vector<uint8_t>>{};
            rpc_wrapper::helper::SerializeArg(Result, Args...);
            return Result;
        }

        std::vector<uint8_t> FlattenSerializedArguments(const std::vector<std::vector<uint8_t>> &SerializedArguments)
        {
            // TODO: Concatenate the items from SerializedArguments using some kind of separator byte sequence.
            (void)SerializedArguments;
            return std::vector<uint8_t>{};
        }

        template <typename T>
        void BuildSig(std::string &Signature, const T &Arg)
        {
            Signature.append("|").append(rpc_serialize::Signature(Arg));
        }

        template <typename THead, typename ...TRest>
        void BuildSig(std::string &Signature, const THead &Head, const TRest &...Rest)
        {
            Signature.append("|").append(rpc_serialize::Signature(Head));
            rpc_wrapper::helper::BuildSig(Signature, Rest...);
        }

        template <typename ...TArgs>
        std::string BuildSignature(const TArgs &...Args)
        {
            auto Result = std::string{};
            rpc_wrapper::helper::BuildSig(Result, Args...);
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
                m_Signature.append(rpc_wrapper::helper::BuildSignature(Args...));
                m_SerializedArguments =
                    rpc_wrapper::helper::FlattenSerializedArguments(
                    rpc_wrapper::helper::SerializeArguments(Args...));
            }
            TRet Execute()
            {
                auto VoidResult = rpc_wrapper::helper::SendRequestAndGetReply(m_Signature, m_SerializedArguments);
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
                m_Signature.append(rpc_wrapper::helper::BuildSignature(Args...));
                m_SerializedArguments =
                    rpc_wrapper::helper::FlattenSerializedArguments(
                    rpc_wrapper::helper::SerializeArguments(Args...));
            }
            void Execute()
            {
                auto VoidResult = rpc_wrapper::helper::SendRequestAndGetReply(m_Signature, m_SerializedArguments);
                (void)VoidResult; // We just throw this away.
            }
        private:
            std::string m_Signature;
            std::vector<uint8_t> m_SerializedArguments;
        };
    }

    template <typename ...TArgs>
    rpc_wrapper::helper::RpcWrapper_c<void, TArgs...>
    MakeVoidWrapper(const char *pFunctionName, const TArgs &...Args)
    {
        return rpc_wrapper::helper::RpcWrapper_c<void, TArgs...>{pFunctionName, Args...};
    }

    template <typename TRet, typename ...TArgs>
    rpc_wrapper::helper::RpcWrapper_c<TRet, TArgs...>
    MakeWrapper(const char *pFunctionName, const TRet &, const TArgs &...Args)
    {
        return rpc_wrapper::helper::RpcWrapper_c<TRet, TArgs...>{pFunctionName, Args...};
    }
}
