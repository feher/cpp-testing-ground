#include <iostream>
#include "a.hpp"

A::A() : restricted{*this} {
}

void A::f() {
    std::cout << "A::f()" << std::endl;
}

void A::g() {
    std::cout << "A::g()" << std::endl;
}

A::Restricted::Restricted(A& p) : parent{p} {
}

void A::Restricted::f() {
    parent.f();
}

void A::Restricted::g() {
    parent.g();
}
