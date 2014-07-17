//
// Implicit non-virtual dtor.
//
// Usually, "delete pBase" does not call "Derived::~Derived()".
// But via shared_ptr, it does, sometimes!!!!
//
// Most likely, shared_ptr has some extra logic built in to do "the right thing".
//
#include <iostream>
#include <memory> // shared_ptr

namespace { namespace here {

class A
{
public:
    ~A() { std::cout << __FUNCTION__ << std::endl; }
};

class Base
{
    // No virtual dtor!
};

class Derived : public here::Base
{
    here::A m_a;
};

class X
{
public:
    explicit X(here::Base *pBase) : m_pBase{pBase} {}
private:
    std::shared_ptr<here::Base> m_pBase;
};

}} // namespace here

void Dtor_01()
{
    {
        std::cout << "\nDelete via Base : A::~A() NOT CALLED" << std::endl;
        here::Base *p = new here::Derived{};
        delete p;
    }
    {
        std::cout << "\nDelete via X::shared_ptr<Base> : A::~A() NOT CALLED" << std::endl;
        here::X x{new here::Derived{}};
    }
    {
        std::cout << "\nDelete via shared_ptr<Base> : A::~A() NOT CALLED" << std::endl;
        here::Base *p = new here::Derived{};
        std::shared_ptr<here::Base> x{p};
    }
    {
        std::cout << "\nDelete via shared_ptr<Base> : A::~A() called" << std::endl;
        std::shared_ptr<here::Base> x{new here::Derived{}};
    }
    {
        std::cout << "\nDelete via make_shared<Derived> : A::~A() called" << std::endl;
        std::shared_ptr<here::Base> x = std::make_shared<here::Derived>();
    }
}
