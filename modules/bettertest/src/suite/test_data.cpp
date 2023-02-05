#include "bettertest/suite/test_data.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/suite/test_suite.h"
#include "bettertest/utils/date.h"

namespace bt
{
    std::string TestData::getType() const { return type; }

    void TestData::create(const TestSuite& suite, std::string testName)
    {
        dateCreated = dateTimeAsString();
        name        = std::move(testName);
        static_cast<void>(suite);
    }

    void TestData::initialize(const TestSuite& suite, const size_t index)
    {
        runnerIndex = index;
        dateLastRun = dateTimeAsString();
        static_cast<void>(suite);
    }

    void TestData::finalize(const TestSuite& suite, const bool pass)
    {
        passing = pass;
        static_cast<void>(suite);
    }

    bool TestData::hasRunnerIndex() const noexcept { return runnerIndex != static_cast<size_t>(-1); }
}  // namespace bt
