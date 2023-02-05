#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <exception>
#include <utility>

namespace bt
{
    /**
     * \brief Try to run the given function and catch any exceptions.
     * \tparam F Function type.
     * \param f Function object.
     * \return Pair. First value is a boolean indicating success (no exceptions) or failure (an exception occurred).
     * Second value is the return value of the function.
     */
    template<typename F>
    auto try_catch(const F& f) -> std::pair<bool, decltype(f())>
    {
        decltype(f()) result;
        auto          success = true;

        try
        {
            result = f();
        }
        catch (const std::exception&)
        {
            success = false;
        }
        catch (...)
        {
            success = false;
        }

        return std::make_pair(success, result);
    }
}  // namespace bt