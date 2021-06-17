#include "testapp/tests.h"

#include "bettertest/exceptions/better_test_error.h"

namespace test
{
    void UnitTest::operator()()
    {
        /*throw bt::BetterTestError("hello");
        compareEQ(1, 2);
        compareEQ(1, 2).info("info msg");
        compareEQ(1, 2).warning("warning msg");
        compareEQ(1, 2).fatal("fatal msg");
        compareEQ(1, 2).warning("warning msg 2");*/
    }

    void UnitTest2::operator()()
    {
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); });
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); }).info("info msg");
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); }).warning("warning msg");
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); }).fatal("fatal msg");
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); }).warning("warning msg 2");
    }

    void UnitTest3::operator()()
    {
        compareEQ(1, 1);
        compareEQ(2, 2);
        compareEQ(3, 3);
        compareGE(1960, 43435).info("This should have been equal");
        compareEQ(356, 44).warning("This should have been equal");
        compareGT(325, 78767);
        compareLT(2343, 4).fatal("This REALLY should have been equal");
        compareEQ(823, 5);
    }

    void UnitTest4::operator()()
    {
        compareEQ(1, 1);
        expectThrow([] {}).fatal("");
    }
}  // namespace test
