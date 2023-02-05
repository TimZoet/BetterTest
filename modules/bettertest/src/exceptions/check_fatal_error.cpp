#include "bettertest/exceptions/check_fatal_error.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <utility>

namespace bt
{
    CheckFatalError::CheckFatalError(std::string message) : BetterTestError(std::move(message)) {}
}  // namespace bt