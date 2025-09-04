#pragma once

#include <string>

namespace TBAB
{
    /**
     * @struct AbilityData
     * @brief A structure to hold ability data loaded from JSON files.
     */
    struct AbilityData
    {
        std::string id;
        std::string name;
        std::string description;
    };
} // namespace TBAB
