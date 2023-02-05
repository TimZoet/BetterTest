#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <memory>
#include <string>

namespace bt
{
    class TestData;
    using TestDataPtr = std::unique_ptr<TestData>;
    class TestSuite;

    /**
     * \brief The TestData class holds all data describing a specific test.
     */
    class TestData
    {
    public:
        /**
         * \brief Unique type name.
         */
        static constexpr char type[] = "default";

        TestData() = default;

        TestData(const TestData&) = default;

        TestData(TestData&&) = default;

        virtual ~TestData() noexcept = default;

        TestData& operator=(const TestData&) = default;

        TestData& operator=(TestData&&) = default;

        /**
         * \brief Get the unique type name.
         * \return Unique type name.
         */
        [[nodiscard]] virtual std::string getType() const;

        /**
         * \brief Create default test data. Called when there is no test file on disk and this test is being run for the first time.
         * \param suite TestSuite.
         * \param testName Test name.
         */
        virtual void create(const TestSuite& suite, std::string testName);

        /**
         * \brief Initialize test data. Called just before running the test.
         * \param suite TestSuite.
         * \param index Index of the runner that will execute this test.
         */
        virtual void initialize(const TestSuite& suite, size_t index);

        /**
         * \brief Finalize test data. Called after running the test.
         * \param suite TestSuite.
         * \param pass Passing state of test.
         */
        virtual void finalize(const TestSuite& suite, bool pass);

        /**
         * \brief Returns whether this test data object has a valid runner index.
         * \return True or false.
         */
        [[nodiscard]] bool hasRunnerIndex() const noexcept;

        ////////////////////////////////////////////////////////////////
        // Member variables.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief Date and time at which this test was created.
         */
        std::string dateCreated;

        /**
         * \brief Date and time at which this test was last run.
         */
        std::string dateLastRun;

        /**
         * \brief Test name.
         */
        std::string name;

        /**
         * \brief Passing state of this test.
         */
        bool passing = false;

        /**
         * \brief Index of the runner that will execute this test. Left at -1 if the test is not being run.
         */
        size_t runnerIndex = static_cast<size_t>(-1);
    };
}  // namespace bt
