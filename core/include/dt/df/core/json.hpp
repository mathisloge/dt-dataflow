#pragma once
#include "base_node.hpp"
#include "dtdfcore_export.h"
#include <nlohmann/json.hpp>

namespace dt::df
{
void DTDFCORE_EXPORT to_json(nlohmann::json &j, const BaseNode &p);
} // namespace dt::df
