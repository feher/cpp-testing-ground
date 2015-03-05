#include <iostream>

#include <vector>
#include <array>
#include <string>

using IndexedVectorPosition = std::vector<int>::size_type;

template<typename ...TIndices>
class TypeToIdMapper final
{
public:
    template<typename T, typename TIndex>
    static int mapIfSameType(int indexId)
    {
        return std::is_same<T, TIndex>::value ? indexId : -1;
    }

    template<typename T>
    static int mapToMatchingType(int)
    {
        return -1;
    }

    template<typename T, typename TFirst, typename ...TRest>
    static int mapToMatchingType(int indexId)
    {
        if(mapIfSameType<T, TFirst>(indexId) != -1)
            return indexId;
        return mapToMatchingType<T, TRest...>(indexId + 1);
    }

    template<typename T>
    static int getTypeId()
    {
        return mapToMatchingType<T, TIndices...>(0);
    }
};


template<typename T,
         typename ...TIndices>
class IndexedVector final
{
public:
    explicit IndexedVector()
        : m_items{},
          m_indices(sizeof...(TIndices))
    {
    }
	~IndexedVector() = default;

    void addItem(const T &item);

    IndexedVectorPosition size() const;

    template<typename TIndex>
    const T& itemAt(const IndexedVectorPosition position) const;

private:
	std::vector<T> m_items;
    std::vector<std::vector<IndexedVectorPosition>> m_indices;
    TypeToIdMapper<TIndices...> m_IndexTypeToIndexId;
};

template<typename T, typename TIndex>
void
helper_addToIndex(
    const int indexId,
    const T &item,
    const IndexedVectorPosition itemRealPosition,
    std::vector<std::vector<IndexedVectorPosition>> &indices,
    std::vector<T> &items)
{
    auto &index = indices[indexId];
    auto indexer = TIndex{};
    auto indexedPositionIt =
        std::upper_bound(
            std::begin(index), std::end(index),
            itemRealPosition,
            [&](const IndexedVectorPosition positionA, const IndexedVectorPosition positionB){
                const auto &itemA = items[positionA];
                const auto &itemB = items[positionB];
                return indexer.IsLess(itemA, itemB);
            });
    index.insert(indexedPositionIt, itemRealPosition);
}

template<typename T>
void
helper_addToIndices(
    const int ,
    const T &,
    const IndexedVectorPosition ,
    std::vector<std::vector<IndexedVectorPosition>> &,
    std::vector<T> &)
{
}

template<typename T, typename TFirst, typename ...TRest>
void
helper_addToIndices(
    const int indexId,
    const T &item,
    const IndexedVectorPosition itemRealPosition,
    std::vector<std::vector<IndexedVectorPosition>> &indices,
    std::vector<T> &vektor)
{
    helper_addToIndex<T, TFirst>(indexId, item, itemRealPosition, indices, vektor);
    helper_addToIndices<T, TRest...>(indexId + 1, item, itemRealPosition, indices, vektor);
}

template<typename T, typename ...TIndices>
void
IndexedVector<T, TIndices...>::addItem(const T &item)
{
    m_items.push_back(item);
    const auto itemRealPosition = m_items.size() - 1;
    helper_addToIndices<T, TIndices...>(
            0, item, itemRealPosition,
            m_indices, m_items);
}

template<typename T, typename ...TIndices>
IndexedVectorPosition
IndexedVector<T, TIndices...>::size() const
{
    return m_items.size();
}

template<typename T, typename ...TIndices>
template<typename TIndex>
const T&
IndexedVector<T, TIndices...>::itemAt(const IndexedVectorPosition position) const
{
    const auto indexId = m_IndexTypeToIndexId.getTypeId<TIndex>();
    const auto realPosition = m_indices[indexId][position];
    return m_items[realPosition];
}

struct MyType
{
    double field1;
    int field2;
    std::string field3;
};

struct SortByField1
{
    bool IsLess(const MyType &a, const MyType &b)
    {
        return a.field1 < b.field1;
    }
};

struct SortByField1AndField3
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
    std::cout << TypeToIdMapper<int, double>{}.getTypeId<double>() << std::endl;

    auto iv =
        IndexedVector<
            MyType,
            SortByField1,
            SortByField1AndField3>{};
    iv.addItem(MyType{ 6.0, 3, "hello" });
    iv.addItem(MyType{ 2.0, 45, "apple" });
    iv.addItem(MyType{ 5.0, 2, "lion" });
    iv.addItem(MyType{ 3.0, 30, "queen" });
    iv.addItem(MyType{ 3.0, 30, "pear" });

    for (auto i = IndexedVectorPosition{ 0 }; i < iv.size(); ++i)
    {
        std::cout << iv.itemAt<SortByField1>(i).field1 << std::endl;
        std::cout << iv.itemAt<SortByField1AndField3>(i).field1 << " "
                  << iv.itemAt<SortByField1AndField3>(i).field3 << std::endl;
    }

    return 0;
}
