#include "bettertest/suite/suite_data.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/suite/test_suite.h"
#include "bettertest/utils/date.h"

namespace bt
{
    std::string SuiteData::getType() const { return type; }

    void SuiteData::create(TestSuite& suite)
    {
        dateCreated = dateTimeAsString();
        name        = suite.getName();
        runIndex    = 0;
        version     = Version::create();
    }

    void SuiteData::initialize(TestSuite& suite)
    {
        dateLastRun = dateTimeAsString();
        runIndex++;
        static_cast<void>(suite);
    }

    void SuiteData::finalize(TestSuite& suite, const bool pass)
    {
        passing = pass;
        static_cast<void>(suite);
    }
}  // namespace bt
