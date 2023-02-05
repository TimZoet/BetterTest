#include "bettertest/mixins/exception_mixin.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <format>

namespace bt
{
    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    std::string ExceptionMixin::getType() const { return type; }

    ////////////////////////////////////////////////////////////////
    // Exceptions.
    ////////////////////////////////////////////////////////////////

    CheckResult ExceptionMixin::expectThrow(const std::function<void()>& callable, const std::source_location& loc)
    {
        auto thrown = false;

        try
        {
            callable();
        }
        catch (...)
        {
            thrown = true;
        }

        if (thrown) return recordResult(result_t::success, loc, "");

        return recordResult(result_t::failure, loc, "Expected an exception");
    }

    CheckResult ExceptionMixin::expectNoThrow(const std::function<void()>& callable, const std::source_location& loc)
    {
        auto        thrown = false;
        std::string message;

        try
        {
            callable();
        }
        catch (const std::exception& e)
        {
            thrown  = true;
            message = e.what();
        }
        catch (...)
        {
            thrown = true;
        }

        if (!thrown) return recordResult(result_t::success, loc, "");

        return recordResult(result_t::failure, loc, std::format("An unexpected exception was thrown: {}", message));
    }
}  // namespace bt
