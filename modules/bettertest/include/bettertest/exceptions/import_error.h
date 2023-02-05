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
     * \brief Exception that is thrown when the importing of test data fails.
     */
    class ImportError final : public BetterTestError
    {
    public:
        explicit ImportError(std::string message);
    };
}  // namespace bt