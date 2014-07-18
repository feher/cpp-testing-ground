#include <string>
#include <iostream>
#include <functional>
#include <utility>
#include <tuple>
#include <type_traits>

//template <>
//struct MakeTuple_s
//{
//
//};
//
//template <typename TFuncRet, typename TFuncArg1, typename ...TFuncArgRest>
//auto ExtractFunctionParameterList(TFuncRet (*pFunction) (TFuncArg1, TFuncArgRest...))
//-> MakeTuple_s<TFuncArg1, TFuncArgRest...>::TupleType
//{
//    return MakeTuple_s<TFuncArg1, TFuncArgRest...>::TupleType{};
//}


template <typename TFuncRet, typename ...TFuncArgs>
std::tuple<typename std::remove_reference<TFuncArgs>::type...>
MakeTupleFromParameterList(TFuncRet (*pFunction) (TFuncArgs...))
{
    return std::tuple<typename std::remove_reference<TFuncArgs>::type...>();
}

void TestFunction(int, const std::string &) {}

int main()
{
    auto ParameterList = MakeTupleFromParameterList(TestFunction);
    std::cout << typeid(ParameterList).name() << std::endl;
    return 0;
}
