#include "c.hpp"

void C::h() {
    // f();             // Error! A::f() is private.
    // g();             // Error! A::g() is private.
    // restricted.f();  // Error! A::Restricted::f() is private.
    // restricted.g();  // Error! A::Restricted::g() is private.
}
