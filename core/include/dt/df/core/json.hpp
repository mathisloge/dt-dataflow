#pragma once
#include <nlohmann/json.hpp>
#include "dtdfcore_export.h"
#include "base_node.hpp"

namespace dt::df
{
    void DTDFCORE_EXPORT to_json(nlohmann::json &j, const BaseNode &p);
} // namespace dt::df
