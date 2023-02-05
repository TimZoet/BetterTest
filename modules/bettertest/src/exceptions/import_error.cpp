#include "bettertest/exceptions/import_error.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <utility>

namespace bt
{
    ImportError::ImportError(std::string message) : BetterTestError(std::move(message)) {}
}  // namespace bt