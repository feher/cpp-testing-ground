#pragma once

#include "a.hpp"

class B : public A {
public:
    void h();
private:
    virtual void g() override;
};
