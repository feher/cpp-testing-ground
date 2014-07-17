//
// I filed a bug report about this here:
// https://connect.microsoft.com/VisualStudio/feedback/details/917875/visual-studio-2013-update-2-c-11-value-and-aggregate-initialization-error
//
//

#include <string>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct D
{
    D() { cout << "D::D()" << endl; }
};

struct B
{
    double g[10];
    std::string str;
    D d;
//    // warning C4351: new behavior: elements of array 'B::g' will be default initialized
//#pragma warning(disable : 4351)
//    B() : g{}, str{}, v{} {}
};

struct C
{
    double g[10];
};

struct A
{
    B b_stuff;
    C c_stuff;
    A() : b_stuff{}, c_stuff{} {}
};

// This is used as a workaround for a VS2013 bug:
// The data array is not zero-initialized:
//
// struct B
// {
//     double data[10];
//     std::string str;
// };
//
// struct A
// {
//     A() : b{} {}
//     B b;
// };
//
// A a{}; // a.b.data contains garbage!
//
// Usage:
//
// struct A : private Zero<A>
// {
//     A() : Zero{this}, b{} {}
//     B b;
// };
//
template <typename T>
struct Zero
{
    explicit Zero(T* pData) { std::memset(pData, 0, sizeof(T)); }
};

struct ZA
{
    B b_stuff;
    C c_stuff;
    Zero<ZA> zero;
    ZA() : zero{this} {}
};

int main()
{
    A a{};
    ZA za{};
    double big[50] = {};
    B bb{};
    //B bbb = {0};

    for(auto b : bb.g) { cout << b << " "; }
    cout << endl;
    cout << "This should be all zeroes:" << endl;
    for(auto b : a.b_stuff.g) { cout << b << " "; }
    cout << endl;
    cout << endl;
    for(auto b : a.c_stuff.g) { cout << b << " "; }
    cout << endl;
    cout << endl;
    for(auto b : big) { cout << b << " "; }
    cout << endl;
    cout << endl;
    for(auto b : za.b_stuff.g) { cout << b << " "; }
    cout << endl;
    cout << endl;
    cout << sizeof(A) << endl;
    cout << sizeof(ZA) << endl;

    //(void)bbb;

    return 0;
}
