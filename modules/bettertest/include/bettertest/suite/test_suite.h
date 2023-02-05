#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/runners/test_runner_interface.h"
#include "bettertest/suite/performance_test_suite.h"
#include "bettertest/suite/unit_test_suite.h"

namespace bt
{
    class SuiteData;
    class IExporter;
    class IImporter;

    /**
     * \brief The TestSuite class is the top-level object from which all tests and data are managed.
     */
    class TestSuite
    {
    public:
        using exporter_callback_t = std::function<std::unique_ptr<IExporter>(const std::filesystem::path&)>;
        using importer_callback_t = std::function<std::unique_ptr<IImporter>(const std::filesystem::path&)>;

        /**
         * \brief Construct a new test suite.
         * \param suiteName Test suite name.
         */
        explicit TestSuite(std::string suiteName);

        TestSuite(const TestSuite&) = delete;

        TestSuite(TestSuite&&) = delete;

        ~TestSuite() = default;

        TestSuite& operator=(const TestSuite&) = delete;

        TestSuite& operator=(TestSuite&&) = delete;

        ////////////////////////////////////////////////////////////////
        // Initialization.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Set the output directory to which all results are written.
         * \param dir Output directory.
         */
        void setOutputDirectory(std::filesystem::path dir);

        /**
         * \brief Set the active suite data.
         * \param suiteData SuiteData.
         */
        void setData(std::unique_ptr<SuiteData> suiteData);

        /**
         * \brief Set the function for creating the exporter.
         * \param f Function.
         */
        void setExporterFunction(exporter_callback_t f);

        /**
         * \brief Set the function for creating the importer.
         * \param f Function.
         */
        void setImporterFunction(importer_callback_t f);

        /**
         * \brief Add a unit test runner.
         * \param runner Unit test runner.
         */
        void addUnitTest(ITestRunnerPtr runner);

        /**
         * \brief Add a performance test runner.
         * \param runner Performance test runner.
         */
        void addPerformanceTest(ITestRunnerPtr runner);

        /**
         * \brief If enabled successful tests are skipped and only failing tests are run. New tests are also classified as failing.
         * \param failingOnly Run failing tests only.
         */
        void setRunFailingOnly(bool failingOnly);

        /**
         * \brief Set the list of filters that is used to enable or disable specific unit tests.
         * \param filters List of filter strings.
         */
        void setUnitTestFilter(const std::vector<std::string>& filters);

        /**
         * \brief Set the list of filters that is used to enable or disable specific performance tests.
         * \param filters List of filter strings.
         */
        void setPerformanceTestFilter(const std::vector<std::string>& filters);

        /**
         * \brief If enabled tests are run in parallel.
         * \param multiThreaded Run tests in parallel.
         */
        void setMultithreaded(bool multiThreaded);

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Get suite name.
         * \return Suite name.
         */
        [[nodiscard]] const std::string& getName() const noexcept;

        /**
         * \brief Get suite data.
         * \return SuiteData.
         */
        [[nodiscard]] SuiteData& getData() const noexcept;

        /**
         * \brief Get const unit test suite.
         * \return UnitTestSuite.
         */
        [[nodiscard]] const UnitTestSuite& getUnitTestSuite() const noexcept;

        /**
         * \brief Get unit test suite.
         * \return UnitTestSuite.
         */
        [[nodiscard]] UnitTestSuite& getUnitTestSuite() noexcept;

        /**
         * \brief Get const performance test suite.
         * \return PerformanceTestSuite.
         */
        [[nodiscard]] const PerformanceTestSuite& getPerformanceTestSuite() const noexcept;

        /**
         * \brief Get performance test suite.
         * \return PerformanceTestSuite.
         */
        [[nodiscard]] PerformanceTestSuite& getPerformanceTestSuite() noexcept;

        ////////////////////////////////////////////////////////////////
        // Run.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Run.
         */
        void operator()();

        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////

    private:
        /**
         * \brief Suite name.
         */
        std::string name;

        /**
         * \brief Output directory.
         */
        std::filesystem::path path;

        /**
         * \brief Pointer to SuiteData.
         */
        std::unique_ptr<SuiteData> data;

        /**
         * \brief Function to create an importer.
         */
        importer_callback_t importer;

        /**
         * \brief Function to create an exporter.
         */
        exporter_callback_t exporter;

        /**
         * \brief Unit test suite.
         */
        UnitTestSuite unitTestSuite;

        /**
         * \brief Performance test suite.
         */
        PerformanceTestSuite performanceTestSuite;
    };
}  // namespace bt
