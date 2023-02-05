#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <functional>
#include <source_location>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/mixin_interface.h"

namespace bt
{
    class ExceptionMixin : public IMixin
    {
    public:
        static constexpr char type[] = "exception";

        ExceptionMixin() = default;

        ExceptionMixin(const ExceptionMixin&) = delete;

        ExceptionMixin(ExceptionMixin&&) = delete;

        ~ExceptionMixin() noexcept override = default;

        ExceptionMixin& operator=(const ExceptionMixin&) = delete;

        ExceptionMixin& operator=(ExceptionMixin&&) = delete;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] std::string getType() const override;

    protected:
        ////////////////////////////////////////////////////////////////
        // Exceptions.
        ////////////////////////////////////////////////////////////////

        CheckResult expectThrow(const std::function<void()>& callable,
                                const std::source_location&  loc = std::source_location::current());

        CheckResult expectNoThrow(const std::function<void()>& callable,
                                  const std::source_location&  loc = std::source_location::current());
    };
}  // namespace bt
