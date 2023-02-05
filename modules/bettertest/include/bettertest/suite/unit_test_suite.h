#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <filesystem>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/runners/unit_test_runner.h"
#include "bettertest/suite/test_data.h"
#include "bettertest/utils/name_filter.h"

namespace bt
{
    class IExporter;

    /**
     * \brief The UnitTestSuite class holds all data and runners for unit tests.
     */
    class UnitTestSuite
    {
    public:
        using TestDataList   = std::vector<TestDataPtr>;
        using TestRunnerList = std::vector<ITestRunnerPtr>;

        UnitTestSuite() = default;

        UnitTestSuite(const UnitTestSuite&) = delete;

        UnitTestSuite(UnitTestSuite&&) = delete;

        ~UnitTestSuite() = default;

        UnitTestSuite& operator=(const UnitTestSuite&) = delete;

        UnitTestSuite& operator=(UnitTestSuite&&) = delete;

        ////////////////////////////////////////////////////////////////
        // Initialization.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Add a unit test runner.
         * \param runner Unit test runner.
         */
        void addTest(ITestRunnerPtr runner);

        /**
         * \brief Set the list of filters that is used to enable or disable specific unit tests.
         * \param filters List of filter strings.
         */
        void setFilter(const std::vector<std::string>& filters);

        /**
         * \brief If enabled successful tests are skipped and only failing tests are run. New tests are also classified as failing.
         * \param failingOnly Run failing tests only.
         */
        void setRunFailingOnly(bool failingOnly) noexcept;

        /**
         * \brief If enabled tests are run in parallel.
         * \param multiThread Run tests in parallel.
         */
        void setMultithreaded(bool multiThread);

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get list of TestData objects.
         * \return TestDataList.
         */
        [[nodiscard]] TestDataList& getData() noexcept;

        /**
         * \brief Get const list of TestData objects.
         * \return TestDataList.
         */
        [[nodiscard]] const TestDataList& getData() const noexcept;

        /**
         * \brief Returns whether all active tests passed.
         * \return True or false.
         */
        [[nodiscard]] bool isPassing() const noexcept;

        ////////////////////////////////////////////////////////////////
        // Run.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Run.
         * \param suite TestSuite.
         * \param exporter Exporter.
         * \param out Output.
         */
        void operator()(const TestSuite& suite, IExporter& exporter, std::ostream& out);
        
    private:
        /**
         * \brief Determine which tests need to run.
         * \param suite TestSuite.
         * \param out Output.
         */
        void resolveTests(const TestSuite& suite, std::ostream& out);

        void runTests(const TestSuite& suite, IExporter& exporter, std::ostream& out);

        void runTestsMultithreaded(const TestSuite& suite, IExporter& exporter, std::ostream& out);

        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief List of all TestData objects.
         */
        TestDataList data;

        /**
         * \brief List of all TestRunner objects.
         */
        TestRunnerList runners;

        /**
         * \brief Filter object.
         */
        NameFilter filter;

        /**
         * \brief Run failing tests only.
         */
        bool runFailingOnly = false;

        bool multiThreaded = false;
    };
}  // namespace bt
