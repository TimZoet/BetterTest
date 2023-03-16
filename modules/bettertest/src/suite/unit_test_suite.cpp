#include "bettertest/suite/unit_test_suite.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <algorithm>
#include <future>
#include <mutex>
#include <ranges>
#include <string>

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "common/ansi_colors.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/output/exporter_interface.h"
#include "bettertest/suite/test_suite.h"

using namespace std::string_literals;

namespace
{
    void printResults(std::ostream& out, const std::stringstream& ss, const bool pass, const bt::ITestRunner& runner)
    {
        const auto s = ss.str();
        if (pass)
            out << ansi_color::fg_black << ansi_color::bg_brightgreen;
        else
            out << ansi_color::fg_black << ansi_color::bg_brightred;
        out << "[ START " << runner.getTestName() << " ]\n";
        out << ansi_color::fg_white << ansi_color::bg_black;
        out << s;
        if (pass)
            out << ansi_color::fg_black << ansi_color::bg_brightgreen;
        else
            out << ansi_color::fg_black << ansi_color::bg_brightred;
        out << "[ END   " << runner.getTestName() << " ]\n";
        out << ansi_color::fg_white << ansi_color::bg_black << std::endl;
    }
}  // namespace

namespace bt
{
    ////////////////////////////////////////////////////////////////
    // Initialization.
    ////////////////////////////////////////////////////////////////

    void UnitTestSuite::addTest(ITestRunnerPtr runner) { runners.emplace_back(std::move(runner)); }

    void UnitTestSuite::setFilter(const std::vector<std::string>& filters) { filter.addFilters(filters); }

    void UnitTestSuite::setRunFailingOnly(const bool failingOnly) noexcept { runFailingOnly = failingOnly; }

    void UnitTestSuite::setMultithreaded(const bool multiThread) { multiThreaded = multiThread; }

    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    auto UnitTestSuite::getData() noexcept -> TestDataList& { return data; }

    auto UnitTestSuite::getData() const noexcept -> const TestDataList& { return data; }

    bool UnitTestSuite::isPassing() const noexcept
    {
        return std::ranges::all_of(
          data.begin(), data.end(), [](const auto& t) { return !t->hasRunnerIndex() || t->passing; });
    }

    ////////////////////////////////////////////////////////////////
    // Run.
    ////////////////////////////////////////////////////////////////

    void UnitTestSuite::operator()(const TestSuite& suite, IExporter& exporter, std::ostream& out)
    {
        resolveTests(suite, out);
        if (multiThreaded) runTestsMultithreaded(suite, exporter, out);
        runTestsSerialized(suite, exporter, out);
    }

    void UnitTestSuite::resolveTests(const TestSuite& suite, std::ostream& out)
    {
        size_t testCount = 0;

        // Create and initialize tests.
        for (size_t i = 0; i < runners.size(); i++)
        {
            const auto& runner = runners[i];

            // Disable tests that do not match pattern.
            const auto& testName = runner->getTestName();
            if (!filter.match(testName, true)) continue;

            // Look for test.

            // Found test, initialize.
            if (const auto it =
                  std::ranges::find_if(data, [&testName](const TestDataPtr& t) { return t->name == testName; });
                it != data.end())
            {
                // Skip non-failing tests.
                if (runFailingOnly && (*it)->passing) continue;

                (*it)->initialize(suite, i);
            }
            // Did not find test, create new and then initialize.
            else
            {
                const auto& t = data.emplace_back(std::make_unique<TestData>());
                t->create(suite, testName);
                t->initialize(suite, i);
            }

            testCount++;
        }

        out << "Running " << testCount << "/" << runners.size() << " tests\n\n";
    }

    void UnitTestSuite::runTestsSerialized(const TestSuite& suite, IExporter& exporter, std::ostream& out) const
    {
        for (const auto& testData : data)
        {
            // Skip tests without a runner.
            if (!testData->hasRunnerIndex()) continue;

            auto& runner = *runners[testData->runnerIndex];

            // Skip tests that can run in parallel when the suite is being run in multithreaded mode.
            if (multiThreaded && runner.isParallel()) continue;

            // Run test.
            std::stringstream ss;
            const auto [pass, error] = runner(suite, exporter, ss);

            // If test failed due to an exception, output error message.
            if (!pass && !error.empty()) ss << "The following error occurred:\n" << error << "\n";

            // Finalize test data.
            testData->finalize(suite, pass);

            // Print output.
            printResults(out, ss, pass, runner);
        }
    }

    void UnitTestSuite::runTestsMultithreaded(const TestSuite& suite, IExporter& exporter, std::ostream& out) const
    {
        std::vector<std::future<void>> tasks;
        std::mutex                     mutex;

        for (auto& testData : data)
        {
            // Skip tests without a runner.
            if (!testData->hasRunnerIndex()) continue;

            auto& runner = *runners[testData->runnerIndex];

            // Skip tests that cannot run in parallel.
            if (!runner.isParallel()) continue;

            tasks.push_back(std::async(std::launch::async, [&] {
                std::stringstream ss;

                // Run test.
                const auto [pass, error] = runner(suite, exporter, ss);

                // If test failed due to an exception, output error message.
                if (!pass && !error.empty()) ss << "The following error occurred:\n" << error << "\n";

                // Finalize test data.
                testData->finalize(suite, pass);

                // Print output.
                {
                    std::scoped_lock lock(mutex);
                    printResults(out, ss, pass, runner);
                }
            }));
        }

        // Wait for all tests to complete.
        std::ranges::for_each(tasks.begin(), tasks.end(), [](auto& t) { t.get(); });
    }
}  // namespace bt
