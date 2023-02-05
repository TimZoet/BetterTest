#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

namespace bt
{
    /**
     * \brief A utility class that takes a vector of strings to match names against, returning false if they do not match.
     * The filter strings can be in 4 forms:
     * 1. "string". All names exactly matching "string" are a match.
     * 2. "string*". All names that start with "string" are a match.
     * 3. "*string". All names that end with "string" are a match.
     * 4. "*string*". All names that contain "string" are a match.
     */
    class NameFilter
    {
    public:
        NameFilter() = default;

        NameFilter(const NameFilter&) = default;

        NameFilter(NameFilter&&) = default;

        explicit NameFilter(const std::vector<std::string>& filters);

        ~NameFilter() = default;

        NameFilter& operator=(const NameFilter&) = default;

        NameFilter& operator=(NameFilter&&) = default;

        void addFilters(const std::vector<std::string>& filters);

        /**
         * \brief Match a name against all the filters in this object.
         * \param name Name string to match.
         * \param emptyIsMatch If no filters were added to this object, always return true.
         * \return True if there is a match, false if none.
         */
        bool match(const std::string& name, bool emptyIsMatch);

    private:
        std::vector<std::string> exact;
        std::vector<std::string> start;
        std::vector<std::string> end;
        std::vector<std::string> contains;
    };
}