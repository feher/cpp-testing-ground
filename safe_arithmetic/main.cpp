#include <iostream>
#include <type_traits>
#include <limits>
#include <vector>
using namespace std;

void f(char) { cout << "f(char)" << endl; }
void f(unsigned char) { cout << "f(unsigned char)" << endl; }
void f(signed char) { cout << "f(signed char)" << endl; }

void g(int) { cout << "g(int)" << endl; }
void g(unsigned int) { cout << "g(unsigned int)" << endl; }
//void g(signed int) { cout << "g(signed int)" << endl; }

#define STD_IS_INT (std::is_integral<T>::value)
#define IS_INT (IsIntegral<T>::value)

#define STD_IS_UNSIGNED_AND_FITS (std::is_unsigned<T>::value && (sizeof(Type) >= sizeof(T)))
#define IS_UNSIGNED_AND_FITS (IsUnsigned<T>::value && (sizeof(Type) >= sizeof(T)))

#define STD_IS_SIGNED_AND_FITS_OR_FITS \
    ( (std::is_signed<T>::value && (sizeof(Type) >= sizeof(T))) \
    || (sizeof(Type) > sizeof(T)) )
#define IS_SIGNED_AND_FITS_OR_FITS \
    ( ((!IsUnsigned<T>::value) &&  (sizeof(Type) >= sizeof(T))) \
    || (sizeof(Type) > sizeof(T)) )

template<typename T>
struct IsIntegral { static const bool value = false; };

template<typename T>
struct IsUnsigned { static const bool value = false; };

enum ExplicitCast
{
    Cast
};

template <typename U>
class SignedIntegral
{
public:
    using Type = U;

    template<typename T, typename = typename std::enable_if<STD_IS_INT && STD_IS_SIGNED_AND_FITS_OR_FITS>::type>
    explicit SignedIntegral(T d) : d_m{d} { cout << __FUNCSIG__ << endl; }
    template<typename T, typename = typename std::enable_if<STD_IS_INT && !STD_IS_SIGNED_AND_FITS_OR_FITS>::type>
    explicit SignedIntegral(T d, ExplicitCast) : d_m{static_cast<Type>(d)} { cout << __FUNCSIG__ << endl; }

    template<typename T, typename = typename std::enable_if<IS_INT && IS_SIGNED_AND_FITS_OR_FITS>::type>
    explicit SignedIntegral(const T &d) : d_m{d.Value()} { cout << __FUNCSIG__ << endl; }
    template<typename T, typename = typename std::enable_if<IS_INT && !IS_SIGNED_AND_FITS_OR_FITS>::type>
    explicit SignedIntegral(const T &d, ExplicitCast) : d_m{static_cast<Type>(d.Value())} { cout << __FUNCSIG__ << endl; }

    SignedIntegral(const SignedIntegral &d) : d_m{d.d_m} { cout << __FUNCSIG__ << endl; }

    explicit operator Type() const { return d_m; }
    Type Value() const { return d_m; }
private:
    Type d_m;
};

template <typename U>
class UnsignedIntegral
{
public:
    using Type = U;

    template<typename T, typename = typename std::enable_if<STD_IS_INT && STD_IS_UNSIGNED_AND_FITS>::type>
    explicit UnsignedIntegral(T d) : d_m{d} { cout << __FUNCSIG__ << endl; }
    template<typename T, typename = typename std::enable_if<STD_IS_INT && !STD_IS_UNSIGNED_AND_FITS>::type>
    explicit UnsignedIntegral(T d, ExplicitCast) : d_m{static_cast<Type>(d)} { cout << __FUNCSIG__ << endl; }

    template<typename T, typename = typename std::enable_if<IS_INT && IS_UNSIGNED_AND_FITS>::type>
    explicit UnsignedIntegral(const T &d) : d_m{d.Value()} { cout << __FUNCSIG__ << endl; }
    template<typename T, typename = typename std::enable_if<IS_INT && !IS_UNSIGNED_AND_FITS>::type>
    explicit UnsignedIntegral(const T &d, ExplicitCast) : d_m{static_cast<Type>(d.Value())} { cout << __FUNCSIG__ << endl; }

    UnsignedIntegral(const UnsignedIntegral &d) : d_m{d.d_m} { cout << __FUNCSIG__ << endl; }

    explicit operator Type() const { return d_m; }
    Type Value() const { return d_m; }
private:
    Type d_m;
};

using Char = SignedIntegral<signed char>;
using Short = SignedIntegral<signed short>;
using Int = SignedIntegral<signed int>;
using Long = SignedIntegral<signed long>;
using LongLong = SignedIntegral<signed long long>;

using UChar = UnsignedIntegral<unsigned char>;
using UShort = UnsignedIntegral<unsigned short>;
using UInt = UnsignedIntegral<unsigned int>;
using ULong = UnsignedIntegral<unsigned long>;
using ULongLong = UnsignedIntegral<unsigned long long>;

template<>
struct IsIntegral<Char> { static const bool value = true; };
template<>
struct IsIntegral<Short> { static const bool value = true; };
template<>
struct IsIntegral<Int> { static const bool value = true; };
template<>
struct IsIntegral<Long> { static const bool value = true; };
template<>
struct IsIntegral<LongLong> { static const bool value = true; };
template<>
struct IsIntegral<UChar> { static const bool value = true; };
template<>
struct IsIntegral<UShort> { static const bool value = true; };
template<>
struct IsIntegral<UInt> { static const bool value = true; };
template<>
struct IsIntegral<ULong> { static const bool value = true; };
template<>
struct IsIntegral<ULongLong> { static const bool value = true; };

template<>
struct IsUnsigned<UChar> { static const bool value = true; };
template<>
struct IsUnsigned<UShort> { static const bool value = true; };
template<>
struct IsUnsigned<UInt> { static const bool value = true; };
template<>
struct IsUnsigned<ULong> { static const bool value = true; };
template<>
struct IsUnsigned<ULongLong> { static const bool value = true; };

template <typename T, typename = std::enable_if<IsIntegral<T>::value>::type>
T operator-(const T &a, const T &b)
{
    return T{static_cast<typename T::Type>(a.Value() - b.Value())};
}

template <typename T, typename = std::enable_if<IsIntegral<T>::value>::type>
bool operator<(const T &a, const T &b)
{
    return a.Value() < b.Value();
}

template <typename T, typename = std::enable_if<IsIntegral<T>::value>::type>
bool operator>(const T &a, const T &b)
{
    return a.Value() > b.Value();
}

Short f() { return Short{40, Cast}; }
//ULong g() { return ULong{-1}; }

Char CharFunc(Char p) { return p; }
Short ShortFunc(Short p) { return p; }
Int IntFunc(Int p) { return p; }
Long LongFunc(Long p) { return p; }
LongLong LongLongFunc(LongLong p) { return p; }

ULong ULongFunc(ULong p) { return p; }

int intFunc(int p) { cout << __FUNCSIG__ << ": " << p << endl; return p; }
unsigned int uintFunc(unsigned int p) { cout << __FUNCSIG__ << ": " << p << endl; return p; }

struct Apple {
    Apple(int a) { cout << __FUNCSIG__ << ": " << a << endl; }
};

int main()
{
    // http://blog.regehr.org/archives/268
    const auto c = static_cast<signed char>(-1);
    const auto uc = std::numeric_limits<unsigned char>::max();
    const auto s = static_cast<signed short>(-1);
    const auto us = std::numeric_limits<unsigned short>::max();
    const auto i = -1;
    const auto ui = std::numeric_limits<unsigned int>::max();
    const auto l = static_cast<signed long>(-1);
    const auto ul = std::numeric_limits<unsigned long>::max();
    const auto ll = static_cast<signed long long>(-1);
    const auto ull = std::numeric_limits<unsigned long long>::max();

    cout << boolalpha;

    // Badness
    auto tmp = Apple(ui);    // DANGER: Implicitly converts unsigned int -> int -> Apple
    // auto tmp = Apple{ui}; // DETECTED DANGER: Narrowing conversion from unsigned int to int
    intFunc(ui);             // DANGER: Implicitly converts unsigned int to int
    uintFunc(i);             // DANGER: Implicitly converts int to unsigned int
    {
        auto s = static_cast<short>(1);
        auto us = static_cast<unsigned short>(-1);
        cout << (s > us) << endl; // DANGER: ???
    }
    {
        auto ll = static_cast<long long>(-1);
        auto ull = static_cast<unsigned long long>(1);
        cout << (ll > ull) << endl; // DANGER: Implicitly converts long long to unsigned long long.
    }
    {
        auto v = std::vector<char>(std::numeric_limits<std::size_t>::max());
        for(int i = 0; i < v.size(); ++i) // DETECTED DANGER: Compiler warning. Signed/unsigned mismatch.
        {
        }
    }
    {
        auto v = std::vector<char>(std::numeric_limits<std::size_t>::max());
        for(auto i = std::vector<char>::size_type{0}; i < v.size(); ++i) // DETECTED DANGER: Compiler warning. Signed/unsigned mismatch.
        {
        }
    }

    // Remedy
    // IntFunc(ui) << endl;  // DETECTED DANGER: int cannot hold unsigned int
    // IntFunc(static_cast<int>(ui)); // DETECTED DANGER: No implicit conversion from int to Int. Otherwise, it would also allow unsigned int -> int -> Int.
    IntFunc(Int{static_cast<int>(ui)}); // OK: Safe and explicit.

    // Int
    // IntFunc(1);        // Error: No implicit conversion from int to Int

    IntFunc(Int(1));   // OK: int can hold int
    IntFunc(Int(c));   // OK: int can hold signed char
    IntFunc(Int(uc));  // OK: int can hold unsigned char
    IntFunc(Int(i));   // OK: int can hold int
    // IntFunc(Int(ui));  // ERROR: int cannot hold unsigned int
    IntFunc(Int(l));   // OK: int can hold long
    // IntFunc(Int(ul));  // ERROR: int cannot hold unsigned long
    // IntFunc(Int(ll));  // ERROR: int cannot hold long long
    // IntFunc(Int(ull)); // ERROR: int cannot hold unsigned long long

    IntFunc(Int{1});   // OK: int can hold int
    IntFunc(Int{c});   // OK: int can hold signed char
    IntFunc(Int{uc});  // OK: int can hold unsigned char
    IntFunc(Int{i});   // OK: int can hold int
    // IntFunc(Int{ui});  // ERROR: int cannot hold unsigned int
    IntFunc(Int{l});   // OK: int can hold long
    // IntFunc(Int{ul});  // ERROR: int cannot hold unsigned long
    // IntFunc(Int{ll});  // ERROR: int cannot hold long long
    // IntFunc(Int{ull}); // ERROR: int cannot hold unsigned long long

    // IntFunc(UInt{1, Cast}); // ERROR: Cannot convert from UInt to Int

    ULongFunc(ULong{-1, Cast} -ULong{12, Cast}); // OK



    //    cout << boolalpha;
    //const auto a = f() - Short{g().Value()};
    //const auto a = f() - Short{g()};
    //    auto a = Long{(unsigned char)'a'};
    //    f('a');
    //    f((unsigned char)('a'));
    //    f((signed char)('a'));
    //    cout << a << endl;
    //    cout << (a < Short{0}) << endl;
    //    cout << static_cast<int>(static_cast<signed char>(-222)) << endl;
    //    cout << static_cast<int>(static_cast<signed char>(0xffffffffUL)) << endl;
}
