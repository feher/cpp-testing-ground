#include <iostream>

namespace util
{

    template <typename T>
    struct Ref
    {
        Ref(T& o) : m_o{o} {}
        operator T&() { return m_o; }
        T& operator=(const T& other) { m_o = other; return *this; }
        T& m_o;
    };

    template <typename T>
    util::Ref<T> ref(T& o)
    {
        return {o};
    }
}

void Func(util::Ref<int> data)
{
    data = 4;
}

int main()
{
    // Func(3); // ERROR: cannot convert argument 1 from 'int' to 'Ref<char>'

    int data = 3;
    Func(util::ref(data)); // OK: Nice. Explicit.
    std::cout << data << std::endl;
}
