#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <concepts>
#include <ostream>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/mixin_interface.h"
#include "bettertest/mixins/mixin_results_getter.h"
#include "bettertest/tests/unit_test_interface.h"

namespace bt
{
    template<typename Derived, std::derived_from<IMixin>... Mixins>
    class UnitTest : public IUnitTest, public Mixins...
    {
    public:
        static constexpr bool isUnitTest = true;

        UnitTest()
        {
            (..., mixins.emplace_back(static_cast<Mixins&>(*this).getType()));
            (..., getters.emplace_back(std::make_unique<MixinResultsGetter<Mixins>>(*this)));
        }

        UnitTest(const UnitTest&) = delete;

        UnitTest(UnitTest&&) = delete;

        ~UnitTest() noexcept override = default;

        UnitTest& operator=(const UnitTest&) = delete;

        UnitTest& operator=(UnitTest&&) = delete;

        void setOutput(std::ostream& output) { (..., Mixins::setOutput(output)); }

        [[nodiscard]] const std::vector<std::string>& getMixins() const noexcept override { return mixins; }

        [[nodiscard]] const std::vector<IMixinResultsGetterPtr>& getResultsGetters() const noexcept override
        {
            return getters;
        }

        [[nodiscard]] bool passing() const noexcept override { return (true && ... && Mixins::isPassing()); }

    private:
        std::vector<std::string>            mixins;
        std::vector<IMixinResultsGetterPtr> getters;
    };

    template<typename T>
    concept IsUnitTest = std::derived_from<T, ITest> && T::isUnitTest;
}  // namespace bt
