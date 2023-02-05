#include "bettertest/exceptions/export_error.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <utility>

namespace bt
{
    ExportError::ExportError(std::string message) : BetterTestError(std::move(message)) {}
}  // namespace bt