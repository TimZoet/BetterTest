#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <cstdint>

namespace bt
{
    struct Version
    {
        uint32_t major = 0;
        uint32_t minor = 0;
        uint32_t patch = 0;

        [[nodiscard]] static Version create() noexcept;
    };
}  // namespace bt
