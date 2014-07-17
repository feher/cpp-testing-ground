#include "b.hpp"
#include <iostream>

void B::h() {
    std::cout << "B::h() enter" << std::endl;
    // ++d;         // Error! A::d is private.
    // f();         // Error! A::f() is private.
    g();            // OK! B::g() is accessible here.
    restricted.f(); // OK! A::Restricted::f() is public here.
    restricted.g(); // OK! A::Restricted::g() is public here.
    std::cout << "B::h() exit" << std::endl;
}

void B::g() {
    std::cout << "B::g()" << std::endl;
}
