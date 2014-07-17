#pragma once

class A {
private:
    void f();
    virtual void g();
    double d;

public:
    A();

    class Restricted {
    private:
        A& parent;
        Restricted(A& p);
        // Proxy functions
        void f();
        void g();
        // Friends of Restricted
        friend class A;
        friend class B;
        friend class D;
    };
    Restricted restricted;
};
