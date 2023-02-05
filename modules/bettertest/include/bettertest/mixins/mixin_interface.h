#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <ostream>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/utils/check_result.h"
#include "bettertest/utils/result.h"

namespace bt
{
    /**
     * \brief The IMixin class defines the interface that all mixins must implement.
     * Mixins can provide methods to perform all sorts of checks. Tests can derive
     * from the mixins to use their functionality. Ideally, a mixin provides a
     * coherent set of methods.
     */
    class IMixin
    {
    public:
        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        IMixin() = default;

        IMixin(const IMixin&) = delete;

        IMixin(IMixin&&) = delete;

        virtual ~IMixin() = default;

        IMixin& operator=(const IMixin&) = delete;

        IMixin& operator=(IMixin&&) = delete;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] virtual bool isPassing() const noexcept;

        /**
         * \brief Get the unique type name.
         * \return Name.
         */
        [[nodiscard]] virtual std::string getType() const = 0;

        /**
         * \brief Get the total number of performed tests.
         * \return Number of tests.
         */
        [[nodiscard]] size_t getTotal() const noexcept;

        /**
         * \brief Get the number of recorded successes.
         * \return Number of successes.
         */
        [[nodiscard]] size_t getSuccesses() const noexcept;

        /**
         * \brief Get the number of recorded failures.
         * \return Number of failures.
         */
        [[nodiscard]] size_t getFailures() const noexcept;

        /**
         * \brief Get the number of recorded exceptions.
         * \return Number of exceptions.
         */
        [[nodiscard]] size_t getExceptions() const noexcept;

        /**
         * \brief Get the full list of results.
         * \return List of results.
         */
        [[nodiscard]] const std::vector<Result>& getResults() const noexcept;

        ////////////////////////////////////////////////////////////////
        // Setters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Set stream to which all output is written.
         * \param output Ostream.
         */
        void setOutput(std::ostream& output);

    protected:
        [[nodiscard]] CheckResult recordResult(result_t r, const std::source_location& loc, const std::string& error);

        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////

        size_t total      = 0;
        size_t successes  = 0;
        size_t failures   = 0;
        size_t exceptions = 0;

        std::vector<Result> results;

        std::ostream* out = nullptr;
    };
}  // namespace bt
