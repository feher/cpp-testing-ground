#pragma once

#include <iostream>

template <typename T>
static void TemplateFunc(T Arg)
{
    Arg = Arg + 1;
    std::cout << Arg << "\n";
}

namespace Source1
{
    void Func();
}

namespace Source2
{
    void Func();
}

