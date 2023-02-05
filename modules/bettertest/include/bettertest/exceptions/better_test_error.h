#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <exception>
#include <string>

namespace bt
{
    /**
     * \brief Base class for all BetterTest exceptions.
     */
    class BetterTestError : public std::exception
    {
    public:
        explicit BetterTestError(std::string message);

        [[nodiscard]] const char* what() const noexcept override;

        [[nodiscard]] const std::string& getMessage() const noexcept;

    private:
        std::string message;
    };
}  // namespace bt