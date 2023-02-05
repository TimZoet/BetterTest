#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <ostream>
#include <string>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/utils/result.h"

namespace bt
{
    class CheckResult
    {
    public:
        CheckResult() = delete;

        CheckResult(result_t result, std::ostream& outstream);

        CheckResult(const CheckResult&) = default;

        CheckResult(CheckResult&&) = default;

        ~CheckResult() = default;

        CheckResult& operator=(const CheckResult&) = default;

        CheckResult& operator=(CheckResult&&) = default;

        void info(const std::string& message) const;

        void warning(const std::string& message) const;

        void fatal(const std::string& message) const;

    private:
        result_t      result;
        std::ostream* out;
    };
}  // namespace bt