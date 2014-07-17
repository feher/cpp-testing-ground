#include <iostream>
#include <functional>
#include <memory>

using namespace std;

struct A {};

void g()
{
    //{
    //    int apple;
    //    int banana;
    //    size_t carrot;
    //    apple = int{banana - carrot};
    //}
    //{
    //    int apple;
    //    int banana;
    //    size_t carrot;
    //    apple = banana - carrot;
    //}
    //{
    //    double d = 0.1;
    //    int c = d;
    //}
    {
        // (~0x5a >> 4) should give us 0x0a
        uint8_t u = 0x5a;
        auto nu = ~u;
        uint8_t x = (~u) >> 4; // Bad: x is 0xfa, no compiler warning!
        auto y = (~u) >> 4; // Better: y is 0xfff...fa, y is int. Easier to notice.
        cout << hex << static_cast<unsigned int>(x) << endl;
        cout << hex << static_cast<unsigned int>(y) << endl;
    }
    {
        double d = 1.2;
        int x = d; // Better: Compiler warning
        auto y = d; // 
        cout << x << y << endl;
    }
    {
        char array[10];
        // char x[10] = array; // Error: not valid C++
        auto y = array; // Bad: y points to array
    }
}

void f(const char a[5])
{
    cout << a << endl;
}

int main()
{
    g();
    char a[10];
    f(a);
    return 0;
}
