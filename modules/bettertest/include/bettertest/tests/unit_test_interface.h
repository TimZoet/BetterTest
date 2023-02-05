#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <concepts>
#include <memory>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/mixin_results_getter.h"
#include "bettertest/tests/test_interface.h"

namespace bt
{
    class IUnitTest : public ITest
    {
    public:
        IUnitTest() = default;

        IUnitTest(const IUnitTest&) = delete;

        IUnitTest(IUnitTest&&) = delete;

        ~IUnitTest() noexcept override = default;

        IUnitTest& operator=(const IUnitTest&) = delete;

        IUnitTest& operator=(IUnitTest&&) = delete;

        [[nodiscard]] virtual const std::vector<std::string>& getMixins() const noexcept = 0;

        [[nodiscard]] virtual const std::vector<IMixinResultsGetterPtr>& getResultsGetters() const noexcept = 0;
    };

    template<typename T>
    concept IsIUnitTest = std::derived_from<T, IUnitTest>;

    using IUnitTestPtr = std::unique_ptr<IUnitTest>;
}  // namespace bt
