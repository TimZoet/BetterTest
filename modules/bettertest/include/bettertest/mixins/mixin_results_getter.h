#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <memory>
#include <vector>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/mixin_interface.h"

namespace bt
{
    struct IMixinResultsGetter
    {
        IMixinResultsGetter() = default;

        IMixinResultsGetter(const IMixinResultsGetter&) = default;

        IMixinResultsGetter(IMixinResultsGetter&&) noexcept = default;

        virtual ~IMixinResultsGetter() = default;

        IMixinResultsGetter& operator=(const IMixinResultsGetter&) = default;

        IMixinResultsGetter& operator=(IMixinResultsGetter&&) noexcept = default;

        [[nodiscard]] virtual size_t getTotal() const noexcept = 0;

        [[nodiscard]] virtual size_t getSuccesses() const noexcept = 0;

        [[nodiscard]] virtual size_t getFailures() const noexcept = 0;

        [[nodiscard]] virtual size_t getExceptions() const noexcept = 0;

        [[nodiscard]] virtual const std::vector<Result>& getResults() const noexcept = 0;
    };

    using IMixinResultsGetterPtr = std::unique_ptr<IMixinResultsGetter>;

    template<typename T>
    struct MixinResultsGetter final : IMixinResultsGetter
    {
        explicit MixinResultsGetter(const T& m) : mixin(&m) {}

        [[nodiscard]] size_t getTotal() const noexcept override { return mixin->getTotal(); }

        [[nodiscard]] size_t getSuccesses() const noexcept override { return mixin->getSuccesses(); }

        [[nodiscard]] size_t getFailures() const noexcept override { return mixin->getFailures(); }

        [[nodiscard]] size_t getExceptions() const noexcept override { return mixin->getExceptions(); }

        [[nodiscard]] const std::vector<Result>& getResults() const noexcept override { return mixin->getResults(); }

        const T* mixin = nullptr;
    };
}  // namespace bt
