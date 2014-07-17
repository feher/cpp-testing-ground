#include <string>
#include <functional>
#include <memory>

template<typename T>
class RAII_c;
template<typename T>
RAII_c<T> MakeRAII(T&& Resource);

template<typename T>
class RAII_c
{
public:
    using ReleaseFunction_t = std::function<void(const T&)>;
    ~RAII_c() { if(m_ReleaseFunction) { m_ReleaseFunction(m_Resource); } }
    void SetReleaseFunction(ReleaseFunction_t ReleaseFunction) { m_ReleaseFunction = ReleaseFunction; }
    const T& GetResource() const { return m_Resource; }
private:
    friend RAII_c MakeRAII<T>(T&& Resource);
    RAII_c(T&& Resource) : m_Resource{std::forward(Resource)} {}
    T m_Resource;
    ReleaseFunction_t m_ReleaseFunction;
};

template<typename T>
RAII_c<T> MakeRAII(T&& Resource)
{
    return RAII_c<T>(std::forward<T>(Resource));
}

int main()
{
    auto s = MakeRAII(std::string{"hi"});
    return 0;
}
