#include "bettertest/utils/version.h"

namespace bt
{
    Version Version::create() noexcept
    {
        return {BETTERTEST_VERSION_MAJOR, BETTERTEST_VERSION_MINOR, BETTERTEST_VERSION_PATCH};
    }
}  // namespace bt
