#include "bettertest/mixins/mixin_interface.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <format>

namespace bt
{
    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    bool IMixin::isPassing() const noexcept { return total == successes; }

    size_t IMixin::getTotal() const noexcept { return total; }

    size_t IMixin::getSuccesses() const noexcept { return successes; }

    size_t IMixin::getFailures() const noexcept { return failures; }

    size_t IMixin::getExceptions() const noexcept { return exceptions; }

    const std::vector<Result>& IMixin::getResults() const noexcept { return results; }

    ////////////////////////////////////////////////////////////////
    // Setters.
    ////////////////////////////////////////////////////////////////

    void IMixin::setOutput(std::ostream& output) { out = &output; }

    CheckResult IMixin::recordResult(const result_t r, const std::source_location& loc, const std::string& error)
    {
        results.emplace_back(r, loc, std::move(error));

        // Print failure.
        if (r != result_t::success)
            *out << std::format("{0}({1}):\n    {2}\n",
                                results.back().location.file_name(),
                                results.back().location.line(),
                                results.back().error);

        total++;
        switch (r)
        {
        case result_t::success: successes++; return {result_t::success, *out};
        case result_t::failure: failures++; return {result_t::failure, *out};
        case result_t::exception: exceptions++; return {result_t::exception, *out};
        default: failures++; return {result_t::failure, *out};
        }
    }
}  // namespace bt
