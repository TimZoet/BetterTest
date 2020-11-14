#include "testapp/tests.h"

namespace test
{
    void UnitTest::operator()()
    {
        compareEQ(1, 2);
        compareEQ(1, 2).info("info msg");
        compareEQ(1, 2).warning("warning msg");
        compareEQ(1, 2).fatal("fatal msg");
        compareEQ(1, 2).warning("warning msg 2");
    }

    void UnitTest2::operator()()
    {
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); });
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); }).info("info msg");
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); }).warning("warning msg");
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); }).fatal("fatal msg");
        expectNoThrow([]() { throw std::runtime_error("hello from lambda"); }).warning("warning msg 2");
    }
}  // namespace test
