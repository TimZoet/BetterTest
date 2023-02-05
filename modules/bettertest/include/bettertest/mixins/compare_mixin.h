#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <format>
#include <string>
#include <source_location>

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "common/type_traits.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/mixin_interface.h"
#include "bettertest/utils/compare.h"
#include "bettertest/utils/to_string.h"

namespace bt
{
    class CompareMixin : public IMixin
    {
    public:
        static constexpr char type[] = "compare";

        CompareMixin() = default;

        CompareMixin(const CompareMixin&) = delete;

        CompareMixin(CompareMixin&&) = delete;

        ~CompareMixin() noexcept override = default;

        CompareMixin& operator=(const CompareMixin&) = delete;

        CompareMixin& operator=(CompareMixin&&) = delete;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] std::string getType() const override;

    protected:
        ////////////////////////////////////////////////////////////////
        // Comparisons.
        ////////////////////////////////////////////////////////////////

        template<typename A>
        CheckResult compareTrue(const A& lhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_true(lhs);
            std::string error = res == result_t::success ? "" : std::format("{0} == true", toString(lhs));
            return recordResult(res, loc, std::move(error));
        }

        template<typename A>
        CheckResult compareFalse(const A& lhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_false(lhs);
            std::string error = res == result_t::success ? "" : std::format("{0} == false", toString(lhs));
            return recordResult(res, loc, std::move(error));
        }

        template<typename A, typename B>
        CheckResult
          compareEQ(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_eq(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} == {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        template<typename A, typename B>
        requires(is_vector_v<A>&& is_vector_v<B>) CheckResult
          compareEQ(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            // First compare sizes.
            if (lhs.size() != rhs.size())
            {
                constexpr auto res   = result_t::failure;
                std::string    error = std::format("size {0} == {1}", lhs.size(), rhs.size());
                return recordResult(res, loc, std::move(error));
            }

            // Then compare elements.
            for (size_t i = 0; i < lhs.size(); i++)
            {
                const auto res = compare_eq(lhs[i], rhs[i]);
                if (res != result_t::success)
                {
                    std::string error = std::format("index[{0}] {1} == {2}", i, toString(lhs[i]), toString(rhs[i]));
                    return recordResult(res, loc, std::move(error));
                }
            }

            return recordResult(result_t::success, loc, "");
        }

        template<typename A, typename B>
        CheckResult
          compareNE(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_ne(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} != {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        template<typename A, typename B>
        CheckResult
          compareLT(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_lt(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} < {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        template<typename A, typename B>
        CheckResult
          compareGT(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_gt(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} > {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        template<typename A, typename B>
        CheckResult
          compareLE(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_le(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} <= {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        template<typename A, typename B>
        CheckResult
          compareGE(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_ge(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} >= {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        template<bool LowerInclusive = true,
                 bool UpperInclusive = true,
                 typename A          = nullptr_t,
                 typename B          = nullptr_t,
                 typename C          = nullptr_t>
        CheckResult compareBetween(const A&                    lower,
                                   const B&                    middle,
                                   const C&                    upper,
                                   const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_between<A, B, C, LowerInclusive, UpperInclusive>(lower, middle, upper);
            std::string error = res == result_t::success ? "" :
                                                           std::format("{0} {1} {2} {3} {4}",
                                                                       toString(lower),
                                                                       LowerInclusive ? "<=" : "<",
                                                                       toString(middle),
                                                                       UpperInclusive ? "<=" : "<",
                                                                       toString(upper));
            return recordResult(res, loc, std::move(error));
        }
    };
}  // namespace bt
