#pragma once

#include "Test.hpp"

#include <memory> // unique_ptr

namespace hotspot { namespace simple {

    namespace impl
    {
        class Simple
        {
        public:
            void run();
        };
    }

    class Simple : public Test
    {
    public:
        Simple();

        virtual void run() override;
    private:
        std::unique_ptr<hotspot::simple::impl::Simple> impl;
    };

}}
