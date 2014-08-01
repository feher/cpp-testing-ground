//
// std::sprintf() is error prone because no type check is done for its arguments at compile time.
// This can lead bugs like this:
//
// auto Message = std::string{"Hi"};
// std::sprintf("%s", Message); // This should be Message.c_str()
//
// With template metaprogramming, it is possible to restrict the types that can be passed
// to sprintf(). For example, we can limit them to built-in standard primitive types.
//
// Future work: With C++11 constexpr, it may be possible to do real type checking of
// the arguments against the format string. For this, the format string must be parsed at
// compile time (hence the need for constexpr).
//

#define _CRT_SECURE_NO_WARNINGS // Allow usage of sprintf() without warning.

#include <iostream>
#include <cstring>

// Allow arithmetic types (int, double, ...).
template <typename T>
inline void CheckSprintfArgumentType(const T&,
    typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr)
{
}

// Allow pointers
template <typename T>
inline void CheckSprintfArgumentType(const T&,
    typename std::enable_if<std::is_pointer<T>::value>::type* = nullptr)
{
}

// Allow char array
template <size_t N>
inline void CheckSprintfArgumentType(const char(&)[N])
{
}

// Allow const char array
template <size_t N>
inline void CheckSprintfArgumentType(char(&)[N])
{
}

// Allow empty argument list
inline void CheckSprintfArgumentTypes()
{
}

template <typename TFirst, typename ...TRest>
inline void CheckSprintfArgumentTypes(TFirst&& First, TRest&& ...Rest)
{
    CheckSprintfArgumentType(std::forward<TFirst>(First));
    CheckSprintfArgumentTypes(std::forward<TRest>(Rest)...);
}

template <typename ...TArgs>
inline int Sprintf(TArgs&& ...Args)
{
    CheckSprintfArgumentTypes(std::forward<TArgs>(Args)...);
    return std::sprintf(std::forward<TArgs>(Args)...);
}

int main()
{
    char Buffer[32];

    // In release builds, Sprintf() will be optimized by the compiler into a direct call to std::sprintf().
    // So, Sprintf causes only compile-time overhead. Runtime is unaffected.
    Sprintf(Buffer, "%s %d", "hi", 21);
    std::cout << Buffer << std::endl;

    // Sprintf(Buffer, "%s %d", std::string{"hi"}, 21); // OK: Does not compile! Cannot pass std::string!
    // std::cout << Buffer << std::endl;

    return 0;
}