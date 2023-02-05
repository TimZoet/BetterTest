#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <concepts>
#include <memory>
#include <string>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/utils/version.h"

namespace bt
{
    class SuiteData;
    using SuiteDataPtr = std::unique_ptr<SuiteData>;
    class TestSuite;

    /**
     * \brief The SuiteData class holds all data describing the test suite.
     */
    class SuiteData
    {
    public:
        /**
         * \brief Unique type name.
         */
        static constexpr char type[] = "default";

        SuiteData() = default;

        SuiteData(const SuiteData&) = default;

        SuiteData(SuiteData&&) = default;

        virtual ~SuiteData() noexcept = default;

        SuiteData& operator=(const SuiteData&) = default;

        SuiteData& operator=(SuiteData&&) = default;

        /**
         * \brief Get the unique type name.
         * \return Unique type name.
         */
        [[nodiscard]] virtual std::string getType() const;

        /**
         * \brief Create default suite data. Called when there is no suite file on disk and this suite is being run for the first time.
         * \param suite TestSuite.
         */
        virtual void create(TestSuite& suite);

        /**
         * \brief Initialize suite data. Called just before running tests.
         * \param suite TestSuite.
         */
        virtual void initialize(TestSuite& suite);

        /**
         * \brief Finalize suite data. Called after running tests.
         * \param suite TestSuite.
         * \param pass Passing state of all tests that were run.
         */
        virtual void finalize(TestSuite& suite, bool pass);

        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Date and time at which this test suite was created.
         */
        std::string dateCreated;

        /**
         * \brief Date and time at which this test suite was last run.
         */
        std::string dateLastRun;

        /**
         * \brief Test suite name.
         */
        std::string name;

        /**
         * \brief Passing state of all tests that were run.
         */
        bool passing = false;

        /**
         * \brief Index of the current run.
         */
        size_t runIndex = 0;

        /**
         * \brief BetterTest version.
         */
        Version version;
    };
}  // namespace bt
