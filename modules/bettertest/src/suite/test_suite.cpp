#include "bettertest/suite/test_suite.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////
// External includes.
////////////////////////////////////////////////////////////////

#include "common/ansi_colors.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/output/exporter_interface.h"
#include "bettertest/output/importer_interface.h"
#include "bettertest/suite/suite_data.h"

using namespace std::string_literals;

namespace bt
{
    TestSuite::TestSuite(std::string suiteName) : name(std::move(suiteName)) {}

    ////////////////////////////////////////////////////////////////
    // Initialization.
    ////////////////////////////////////////////////////////////////

    void TestSuite::setOutputDirectory(std::filesystem::path dir) { path = std::move(dir); }

    void TestSuite::setData(std::unique_ptr<SuiteData> suiteData) { data = std::move(suiteData); }

    void TestSuite::setExporterFunction(exporter_callback_t f) { exporter = std::move(f); }

    void TestSuite::setImporterFunction(importer_callback_t f) { importer = std::move(f); }

    void TestSuite::addUnitTest(ITestRunnerPtr runner) { unitTestSuite.addTest(std::move(runner)); }

    void TestSuite::addPerformanceTest(ITestRunnerPtr runner) { performanceTestSuite.addTest(std::move(runner)); }

    void TestSuite::setRunFailingOnly(const bool failingOnly)
    {
        unitTestSuite.setRunFailingOnly(failingOnly);
        performanceTestSuite.setRunFailingOnly(failingOnly);
    }

    void TestSuite::setUnitTestFilter(const std::vector<std::string>& filters) { unitTestSuite.setFilter(filters); }

    void TestSuite::setPerformanceTestFilter(const std::vector<std::string>& filters)
    {
        performanceTestSuite.setFilter(filters);
    }

    void TestSuite::setMultithreaded(const bool multiThreaded) { unitTestSuite.setMultithreaded(multiThreaded); }

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    const std::string& TestSuite::getName() const noexcept { return name; }

    SuiteData& TestSuite::getData() const noexcept { return *data; }

    const UnitTestSuite& TestSuite::getUnitTestSuite() const noexcept { return unitTestSuite; }

    UnitTestSuite& TestSuite::getUnitTestSuite() noexcept { return unitTestSuite; }

    const PerformanceTestSuite& TestSuite::getPerformanceTestSuite() const noexcept { return performanceTestSuite; }

    PerformanceTestSuite& TestSuite::getPerformanceTestSuite() noexcept { return performanceTestSuite; }

    ////////////////////////////////////////////////////////////////
    // Run.
    ////////////////////////////////////////////////////////////////

    void TestSuite::operator()()
    {
        // Try to read suite file. If it did not exist, create default suite data object.
        {
            if (const auto imp = importer(path); !imp->readSuite(*this)) data->create(*this);
        }

        // Initialize suite data.
        data->initialize(*this);

        const auto exp = exporter(path);

        // Run unit test suite.
        unitTestSuite(*this, *exp, std::cout);

        // Finalize suite data.
        data->finalize(*this, unitTestSuite.isPassing());

        // Write suite file.
        exp->writeSuite(*this);

        std::cout << std::endl;

        if (data->passing)
        {
            std::cout << ansi_color::fg_black << ansi_color::bg_brightgreen;
            std::cout << "Done. All tests succeeded\n";
        }
        else
        {
            std::cout << ansi_color::fg_black << ansi_color::bg_brightred;
            std::cout << "Done. One or more tests failed\n";
        }

        std::cout << ansi_color::fg_white << ansi_color::bg_black;
    }
}  // namespace bt
