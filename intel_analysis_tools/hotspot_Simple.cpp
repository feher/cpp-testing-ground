#include "hotspot_Simple.hpp"

namespace { namespace here {

}};

namespace hotspot { namespace simple {

    namespace impl {

        static const auto maxIterations = 5000000;

        double doWork1()
        {
            auto r = 0.0;
            for (auto i = 0; i < hotspot::simple::impl::maxIterations; ++i)
            {
                r *= sqrt(r + i) * (r + i) / 2.0;
            }
            return r;
        }

        double doWork2()
        {
            auto r = 0.0;
            for(auto i = 0; i < hotspot::simple::impl::maxIterations * 2; ++i)
            {
                r *= sqrt(r + i*2) * (r - i) / 1.5;
            }
            return r;
        }

        void hotspot::simple::impl::Simple::run()
        {
            hotspot::simple::impl::doWork1();
            hotspot::simple::impl::doWork2();
        }

    }

    Simple::Simple()
        : impl { new hotspot::simple::impl::Simple{} }
    {
    }

    void Simple::run()
    {
        impl->run();
    }

}}
