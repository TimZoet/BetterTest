#include "bettertest/exceptions/better_test_error.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <utility>

namespace bt
{
    BetterTestError::BetterTestError(std::string message) : message(std::move(message)) {}

    const char* BetterTestError::what() const noexcept { return message.c_str(); }

    const std::string& BetterTestError::getMessage() const noexcept { return message; }
}  // namespace bt