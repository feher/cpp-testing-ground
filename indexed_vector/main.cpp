#include <iostream>

#include <vector>
#include <array>
#include <string>

using IndexedVectorPosition = std::vector<int>::size_type;

template<typename ...T>
class IndexId
{
public:
    static IndexedVectorPosition getIndexId(const T1 *) { return 0; }
    static IndexedVectorPosition getIndexId(const T2 *) { return 1; }
};

template<typename ...TIndices>
struct TemplateArgCount
{
    static int count(TIndices... &Args)
    {
        return sizeof...(Args);
    }
};

template<typename T,
         typename ...TIndices>
class IndexedVector
{
public:
    explicit IndexedVector()
        : m_vector{},
          m_indices{}
    {
        m_indices.reserve(TemplateArgCount<TIndices...>::count());
    }
	~IndexedVector() = default;

    void addItem(const T &item);

    IndexedVectorPosition size() const;

    template<typename TIndex>
    const T& itemAt(const IndexedVectorPosition position) const;

private:
	std::vector<T> m_vector;
    std::vector<std::vector<IndexedVectorPosition>> m_indices;
    IndexId<TIndices...> m_indexIds;
};

template<typename T, typename TIndex>
void
helper_insertSorted(
    const T &item,
    const IndexedVectorPosition itemRealPosition,
    indexIds,
    std::vector<std::vector<IndexedVectorPosition>> indices,
    std::vector<T> &vektor)
{
    const auto indexId = indexIds.getIndexId((const TIndex*)nullptr);
    auto &index = indices[indexId];
    auto indexer = TIndex{};
    auto i = IndexedVectorPosition{0};
    for (; i < index.size(); ++i)
    {
        auto &itemI = vektor[index[i]];
        if (indexer.IsLess(itemI, item))
        {
            continue;
        }
        break;
    }
    auto it = std::begin(index) + i;
    index.insert(it, itemRealPosition);
}

template<typename T, typename TFirst, typename ...TRest>
void
helper_insertSorted(
    const T &item,
    const IndexedVectorPosition itemRealPosition,
    indexIds,
    indices,
    vektor)
{
    helper_insertSorted<T, TFirst>(item, itemRealPosition, indexIds, indices, vektor);
    helper_insertSorted<T, TRest...>(item, itemRealPosition, indexIds, indices, vektor);
}

template<typename T, typename ...TIndices>
void
IndexedVector<T, TIndices...>::addItem(const T &item)
{
    m_vector.push_back(item);
    const auto itemRealPosition = m_vector.size() - 1;
    helper_insertSorted<T, TIndices...>(
            item, itemRealPosition,
            m_indexIds, m_indices, m_vector);
}

template<typename T, typename TIndex1, typename TIndex2>
typename IndexedVector<T, TIndex1, TIndex2>::Position
IndexedVector<T, TIndex1, TIndex2>::size() const
{
    return m_vector.size();
}

template<typename T, typename TIndex1, typename TIndex2>
template<typename TIndex>
const T&
IndexedVector<T, TIndex1, TIndex2>::itemAt(const Position position) const
{
    const auto indexId = m_indexIds.getIndexId((const TIndex*)nullptr);
    const auto realPosition = m_indices[indexId][position];
    return m_vector[realPosition];
}

struct MyType
{
    double field1;
    int field2;
    std::string field3;
};

struct IndexByField1
{
    bool IsLess(const MyType &a, const MyType &b)
    {
        return a.field1 < b.field1;
    }
};

struct IndexByField1AndField3
{
    bool IsLess(const MyType &a, const MyType &b)
    {
        if (a.field1 < b.field1)
        {
            return true;
        }
        if (a.field1 > b.field1)
        {
            return false;
        }
        return a.field3 < b.field3;
    }
};

int main()
{
    auto iv =
        IndexedVector<
            MyType,
            IndexByField1,
            IndexByField1AndField3>{};
    iv.addItem(MyType{ 6.0, 3, "hello" });
    iv.addItem(MyType{ 2.0, 45, "apple" });
    iv.addItem(MyType{ 5.0, 2, "lion" });
    iv.addItem(MyType{ 3.0, 30, "queen" });
    iv.addItem(MyType{ 3.0, 30, "pear" });

    for (auto i = IndexedVectorPosition{ 0 }; i < iv.size(); ++i)
    {
        std::cout << iv.itemAt<IndexByField1>(i).field1 << std::endl;
        std::cout << iv.itemAt<IndexByField1AndField3>(i).field1 << " "
                  << iv.itemAt<IndexByField1AndField3>(i).field3 << std::endl;
    }

    return 0;
}
