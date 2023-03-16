#include "bettertest/runners/test_runner_interface.h"

namespace bt
{
    const std::string& ITestRunner::getTestName() const noexcept { return testName; }

    void ITestRunner::setTestName(std::string name)
    {
        testName = std::move(name);

        // Remove all occurrences of ':'.
        size_t i = 0;
        while (true)
        {
            i = testName.find(':', i);
            if (i == std::string::npos) break;
            testName.replace(i, 1, "");
        }
    }
}  // namespace bt
