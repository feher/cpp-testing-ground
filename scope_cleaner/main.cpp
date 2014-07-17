#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <functional>


class Cleanup_c
{
public:
    using CleanupFunction_t = std::function < void() > ;
    explicit Cleanup_c(CleanupFunction_t Action) : m_Action{Action}
    {
    }
    Cleanup_c(const Cleanup_c&); // Not implemented. Needed for "auto Var = Value;" initializations.
    Cleanup_c(Cleanup_c &&Other) : m_Action{std::move(Other.m_Action)}
    {
        Other.SetAction(nullptr);
    }
    ~Cleanup_c()
    {
        if(m_Action)
        {
            m_Action();
        }
    }
    void SetAction(CleanupFunction_t Action)
    {
        m_Action = Action;
    }
    void Execute()
    {
        if(m_Action)
        {
            m_Action();
        }
    }
private:
    CleanupFunction_t m_Action;
};

int main()
{
    {
        auto FreeThis = Cleanup_c{[](){ std::cout << "im freeing" << std::endl; }};
        FreeThis.SetAction([](){ std::cout << "im freeing otherly" << std::endl; });
        FreeThis.SetAction(nullptr);
    }
    std::cout << "Ende" << std::endl;
    {
        auto s = std::string{"a"}.find("haha", std::string::npos);
        std::cout << s;
    }
    return 0;
}
