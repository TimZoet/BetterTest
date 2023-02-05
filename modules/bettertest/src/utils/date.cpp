#include "bettertest/utils/date.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <chrono>
#include <sstream>

////////////////////////////////////////////////////////////////
// External includes.
////////////////////////////////////////////////////////////////

#include "date/date.h"

using namespace date;

namespace bt
{
    std::string dateTimeAsString()
    {
        const auto now   = std::chrono::system_clock::now();
        const auto today = date::floor<days>(now);

        std::stringstream ss;

        date::operator<<(ss, today) << ' ' << make_time(now - today) << " UTC";

        return ss.str();
    }
}  // namespace bt