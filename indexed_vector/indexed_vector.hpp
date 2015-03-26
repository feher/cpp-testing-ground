#include <iostream>

#include <vector>
#include <array>

namespace feher
{

    using IndexedVectorPosition = std::vector<int>::size_type;

    namespace helper
    {
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
                {
                    return indexId;
                }
                return mapToMatchingType<T, TRest...>(indexId + 1);
            }

            template<typename T>
            static int getTypeId()
            {
                return mapToMatchingType<T, TIndices...>(0);
            }
        };

        namespace indexed_vector
        {
            template<typename T, typename TIndex>
            void
                addToIndex(
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
            void addToIndices(
                const int,
                const T &,
                const IndexedVectorPosition,
                std::vector<std::vector<IndexedVectorPosition>> &,
                std::vector<T> &)
            {
            }

            template<typename T, typename TFirst, typename ...TRest>
            void addToIndices(
                const int indexId,
                const T &item,
                const IndexedVectorPosition itemRealPosition,
                std::vector<std::vector<IndexedVectorPosition>> &indices,
                std::vector<T> &vektor)
            {
                addToIndex<T, TFirst>(indexId, item, itemRealPosition, indices, vektor);
                addToIndices<T, TRest...>(indexId + 1, item, itemRealPosition, indices, vektor);
            }
        }

    }

    template<typename T, typename ...TIndices>
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
        helper::TypeToIdMapper<TIndices...> ms_indexTypeToIndexId;
    };

    template<typename T, typename ...TIndices>
    void IndexedVector<T, TIndices...>::addItem(const T &item)
    {
        m_items.push_back(item);
        const auto itemRealPosition = m_items.size() - 1;
        helper::indexed_vector::addToIndices<T, TIndices...>(
            0, item, itemRealPosition,
            m_indices, m_items);
    }

    template<typename T, typename ...TIndices>
    IndexedVectorPosition IndexedVector<T, TIndices...>::size() const
    {
        return m_items.size();
    }

    template<typename T, typename ...TIndices>
    template<typename TIndex>
    const T& IndexedVector<T, TIndices...>::itemAt(const IndexedVectorPosition position) const
    {
        const auto indexId = ms_indexTypeToIndexId.getTypeId<TIndex>();
        const auto realPosition = m_indices[indexId][position];
        return m_items[realPosition];
    }

}

