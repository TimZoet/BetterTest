#include "bettertest/run.h"
#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/tests/unit_test.h"

class UnitTest01 : public bt::UnitTest<UnitTest01, bt::CompareMixin>
{
public:
    void operator()() override
    {
        compareEQ(42, 42);
        compareLT(10, 20);
        compareBetween(0, 200, 100);
    }
};

int main(int argc, char** argv)
{
    bt::run<UnitTest01>(argc, argv, "myFirstTestSuite");
    return 0;
}