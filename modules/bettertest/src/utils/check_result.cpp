#include "bettertest/utils/check_result.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <format>

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "common/ansi_colors.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/exceptions/check_fatal_error.h"

using namespace std::string_literals;

namespace bt
{
    CheckResult::CheckResult(const result_t result, std::ostream& outstream) : result(result), out(&outstream) {}

    void CheckResult::info(const std::string& message) const
    {
        if (result != result_t::success)
            *out << std::format("    {0}{1}Info:{2}{3} {4}\n",
                                ansi_color::fg_black,
                                ansi_color::bg_white,
                                ansi_color::fg_white,
                                ansi_color::bg_black,
                                message.empty() ? "<no message>" : message);
    }

    void CheckResult::warning(const std::string& message) const
    {
        if (result != result_t::success)
            *out << std::format("    {0}{1}Warning:{2}{3} {4}\n",
                                ansi_color::fg_black,
                                ansi_color::bg_brightyellow,
                                ansi_color::fg_white,
                                ansi_color::bg_black,
                                message.empty() ? "<no message>" : message);
    }

    void CheckResult::fatal(const std::string& message) const
    {
        if (result != result_t::success)
        {
            *out << std::format("    {0}{1}Fatal:{2}{3} {4}\n",
                                ansi_color::fg_black,
                                ansi_color::bg_brightred,
                                ansi_color::fg_white,
                                ansi_color::bg_black,
                                message.empty() ? "<no message>" : message);
            throw CheckFatalError(message);
        }
    }
}  // namespace bt
