#include "multiindex_test.hpp"

#include "boost/multi_index_container.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/member.hpp"

#include <string>

namespace { namespace here
{

    struct Widget
    {
        double d;
        std::string s;
        int i;
    };

    using WidgetTable =
        boost::multi_index_container <
            Widget,
            boost::multi_index::indexed_by<
                boost::multi_index::ordered_non_unique<
                    boost::multi_index::member<
                        Widget, double, &Widget::d>
                >
            >
        >;

    void test()
    {
        auto widgets = WidgetTable{};
        widgets.insert();
    }

}}

void multiindex_test::test()
{
}
