#include "bettertest/mixins/invalid_code_mixin.h"

#include <algorithm>

namespace bt
{
    ////////////////////////////////////////////////////////////////
    // Getters.
    ////////////////////////////////////////////////////////////////

    bool InvalidCodeMixin::isPassing() const noexcept { return rejections == tests; }

    ////////////////////////////////////////////////////////////////
    // Export.
    ////////////////////////////////////////////////////////////////

    void InvalidCodeMixin::exportResults(nlohmann::json& data) const { data[getName()] = nlohmann::json(); }

    void InvalidCodeMixin::exportResults(pugi::xml_node&) const
    {
        //auto xml = node.append_child(getName().c_str());
    }
}  // namespace bt
