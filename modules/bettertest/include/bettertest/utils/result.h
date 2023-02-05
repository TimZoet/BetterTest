#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cstdint>
#include <source_location>
#include <string>

namespace bt
{
    enum class result_t : uint32_t
    {
        failure   = 0,
        success   = 1,
        exception = 2
    };

    struct Result
    {
        result_t             status;
        std::source_location location;
        std::string          error;
    };
}  // namespace bt
