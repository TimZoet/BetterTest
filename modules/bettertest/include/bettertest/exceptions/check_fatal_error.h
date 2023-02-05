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
     * \brief Exception that is thrown when a failing check terminates a test.
     */
    class CheckFatalError final : public BetterTestError
    {
    public:
        explicit CheckFatalError(std::string message);
    };
}  // namespace bt