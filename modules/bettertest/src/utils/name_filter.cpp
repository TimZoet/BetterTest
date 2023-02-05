#include "bettertest/utils/name_filter.h"

#include <algorithm>

namespace bt
{
    NameFilter::NameFilter(const std::vector<std::string>& filters) { addFilters(filters); }

    void NameFilter::addFilters(const std::vector<std::string>& filters)
    {
        // Put all filters in the appropriate list.
        for (const auto& f : filters)
        {
            if (f.starts_with('*'))
            {
                if (f.ends_with('*'))
                {
                    if (f.size() > 2) contains.push_back(f.substr(1, f.size() - 2));
                }
                else
                {
                    if (f.size() > 1) end.push_back(f.substr(1, f.size() - 1));
                }
            }
            else if (f.ends_with('*'))
            {
                if (f.size() > 1) start.push_back(f.substr(0, f.size() - 1));
            }
            else
            {
                exact.push_back(f);
            }
        }
    }

    bool NameFilter::match(const std::string& name, const bool emptyIsMatch)
    {
        // If emptyIsMatch is true and there are no filters, return true.
        if (emptyIsMatch && exact.empty() && start.empty() && end.empty() && contains.empty()) return true;

        // Test if there are any filters that match.

        if (std::ranges::any_of(exact.begin(), exact.end(), [&name](const std::string& f) {
                return f.size() == name.size() && f == name;
            }))
            return true;

        if (std::ranges::any_of(start.begin(), start.end(), [&name](const std::string& f) {
                return f.size() <= name.size() && name.starts_with(f);
            }))
            return true;

        if (std::ranges::any_of(end.begin(), end.end(), [&name](const std::string& f) {
                return f.size() <= name.size() && name.ends_with(f);
            }))
            return true;

        if (std::ranges::any_of(contains.begin(), contains.end(), [&name](const std::string& f) {
                return f.size() <= name.size() && name.find(f) != std::string::npos;
            }))
            return true;

        // No matches.
        return false;
    }
}  // namespace bt
