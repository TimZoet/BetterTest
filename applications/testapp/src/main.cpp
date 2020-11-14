#include <iostream>

#include "testapp/tests.h"
#include "bettertest/run.h"

#ifdef WIN32
#include "Windows.h"
#endif

int main(int argc, char** argv)
{
    // Set path next to executable.
#ifdef WIN32
    {
        WCHAR path[MAX_PATH];
        GetModuleFileNameW(NULL, path, MAX_PATH);
        std::filesystem::path workdir(path);
        const auto            p = workdir.parent_path();
        std::filesystem::current_path(p);
    }
#endif
    bt::run<test::UnitTest, test::UnitTest2>(
      argc, argv, "testapp");
    return 0;
}
