#include "b.hpp"
#include "c.hpp"
#include "d.hpp"

int main() {
    auto b = B{};
    b.h();
    // b.f(); // Error! A::f() is private.
    // b.g(); // Error! B::g() is private.
    // b.restricted.f(); // Error! A::Restricted::f() is private.

    auto c = C{};
    c.h();

    auto d = D{};
    d.h(b);
    return 0;
}
