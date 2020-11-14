#pragma once

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/mixins/exception_mixin.h"
#include "bettertest/tests/unit_test.h"

namespace test
{
    class UnitTest : public bt::UnitTest<UnitTest, bt::CompareMixin>
    {
    public:
        void operator()() override;
    };

    class UnitTest2 : public bt::UnitTest<UnitTest2, bt::ExceptionMixin>
    {
    public:
        void operator()() override;
    };
}  // namespace app
