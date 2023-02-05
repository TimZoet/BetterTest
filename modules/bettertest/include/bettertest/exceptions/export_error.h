#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <string>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/exceptions/better_test_error.h"

namespace bt
{
    /**
     * \brief Exception that is thrown when the exporting of test data fails.
     */
    class ExportError final : public BetterTestError
    {
    public:
        explicit ExportError(std::string message);
    };
}  // namespace bt