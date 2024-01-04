#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <type_traits>

namespace bt
{
    template<typename T>
    concept streamable = requires(T val, std::stringstream s)
    {
        {s << val};
    };

    template<typename T>
    concept stringable = requires(T val)
    {
        {std::to_string(val)};
    };

    template<typename T>
    std::string toString(const T& value)
    {
        if constexpr (std::is_same_v<T, std::string>)
            return value;
        else if constexpr (std::is_convertible_v<T, std::string>)
            return static_cast<std::string>(value);
        else if constexpr (streamable<T>)
        {
            std::stringstream s;
            s << value;
            return s.str();
        }
        else if constexpr (stringable<T>)
            return std::to_string(value);
        else if constexpr (std::is_enum_v<T>)
            return std::to_string(static_cast<std::underlying_type_t<T>>(value));
        else
            return std::string("<not-printable>");
    }
}  // namespace bt
