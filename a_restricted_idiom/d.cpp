#include "d.hpp"
#include "a.hpp"

void D::h(A& a) {
    // a.f();            // Error! A::f() is private.
    // a.g();            // Error! A::g() is private.
    a.restricted.f(); // OK! A::Restricted::f() is public here.
    a.restricted.g(); // OK! A::Restricted::g() is public here.
}
