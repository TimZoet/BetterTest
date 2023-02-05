#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <concepts>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/mixin_interface.h"
#include "bettertest/tests/test_interface.h"

namespace bt
{
    template<typename Derived, std::derived_from<IMixin>... Mixins>
    class PerformanceTest : public ITest, public virtual Mixins...
    {
    public:
        static constexpr bool isPerformanceTest = true;

        PerformanceTest() = default;

        PerformanceTest(const PerformanceTest&) = delete;

        PerformanceTest(PerformanceTest&&) = delete;

        ~PerformanceTest() noexcept override = default;

        PerformanceTest& operator=(const PerformanceTest&) = delete;

        PerformanceTest& operator=(PerformanceTest&&) = delete;

        [[nodiscard]] bool passing() const noexcept override { return (true && ... && Mixins::template isPassing()); }
    };

    template<typename T>
    concept IsPerformanceTest = std::derived_from<T, ITest> && T::isPerformanceTest;
}  // namespace bt
