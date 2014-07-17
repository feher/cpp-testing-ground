//
// Implicit non-virtual dtor.
//
// Usually, "delete pBase" does not call "Derived::~Derived()".
// But via shared_ptr, it does, sometimes!!!!
//
// Most likely, shared_ptr has some extra logic built in to do "the right thing".
// The extra logic is this: http://marcoarena.wordpress.com/2014/04/12/ponder-the-use-of-unique_ptr-to-enforce-the-rule-of-zero/
//
// [QUOTE]
// One of the(many) differences between unique and shared pointers is the deleter. Both can
// have a custom deleter, but in  unique_ptr the deleter is part of the type signature
// (namely, unique_ptr<T, Deleter>) and for shared_ptr is not : shared_ptr has a type - erased
// deleter (and in fact also a type - erased allocator).
//
// This implies that shared_ptr<B> has a deleter which internally remembers that the real type is B.
//
// Consider the example I borrowed from the article : when make_shared<B> is invoked, a shared_ptr<B>
// is constructed as expected. shared_ptr<B> constructs a deleter which will delete the B*.
// Later, shared_ptr<B> is passed to shared_ptr<A>’s constructor : since A* and B*
// are compatible pointers, shared_ptr<B>’s deleter is “shared” as well. So even if the type of the
// object is  shared_ptr<A>, its deleter still remembers to delete a pointer of type B*.
// [END QUOTE]
//
#include <iostream>
#include <memory> // shared_ptr

namespace {
    namespace here {

        class A
        {
        public:
            ~A() { std::cout << __FUNCTION__ << std::endl; }
        };

        class Base
        {
        public:
            // If we add a VIRTUAL dtor here, A::~A() is always called.
            virtual ~Base() { std::cout << __FUNCTION__ << std::endl; }
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

    }
} // namespace here

void Dtor_02()
{
    {
        std::cout << "\nDelete via Base : A::~A() CALLED" << std::endl;
        here::Base *p = new here::Derived{};
        delete p;
    }
    {
        std::cout << "\nDelete via X::shared_ptr<Base> : A::~A() CALLED" << std::endl;
        here::X x{new here::Derived{}};
    }
    {
        std::cout << "\nDelete via shared_ptr<Base> : A::~A() called" << std::endl;
        std::shared_ptr<here::Base> x = std::shared_ptr<here::Base>{new here::Derived{}};
    }
    {
        std::cout << "\nDelete via make_shared<Derived> : A::~A() called" << std::endl;
        std::shared_ptr<here::Base> x = std::make_shared<here::Derived>();
    }
}
