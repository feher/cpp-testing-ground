#include <iterator>
#include <vector>
#include <cstddef>

template<typename T>
class TypeIterator_c : public std::iterator<std::input_iterator_tag, T>
{
public:
    bool operator==(const TypeIterator_c& other) const
    {
        return GetValue() == other.GetValue();
    }
 
    bool operator!=(const TypeIterator_c& other) const
    {
      return !(*this == other);
    }

    const T& operator*() const
    {
        return GetValue();
    }

    T& operator*()
    {
        return GetValue();
    }

    TypeIterator_c& operator++()
    {
        Next();
        return *this;
    }

    TypeIterator_c& begin()
    {
        return Begin();
    }
 
    TypeIterator_c& end()
    {
        return End();
    }

private:
    virtual TypeIterator_c& Begin() = 0;
    virtual TypeIterator_c& End() = 0;
    virtual const T& GetValue() const = 0;
    virtual T& GetValue() = 0;
    virtual void Next() = 0;
};

void Test(TypeIterator_c<int> &IntIterator)
{
    for(const auto Value : IntIterator)
    {

    }
}

struct Data
{
    int i;
    double d;
};

std::vector<Data> DataVector;

template <typename TCont, typename TComp, typename T, size_t O>
class MemberIterator_c : public TypeIterator_c<T>
{
public:
    MemberIterator_c(TCont &Container) : m_Container{Container}
    {}
private:
    virtual MemberIterator_c& Begin() override { m_Iterator = std::begin(m_Container); return *this; }
    virtual MemberIterator_c& End() override { return MemberIterator_c }
    virtual const T& GetValue() const override {}
    virtual T& GetValue() override {}
    virtual void Next() override {}

    TCont &m_Container;
    typename TCont::iterator_type m_Iterator;
};

int main(void)
{
    MemberIterator_c<std::vector<Data>, int, offsetof(Data, i)>
}
