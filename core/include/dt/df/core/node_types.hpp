#pragma once
#include "base_slot.hpp"
#include <memory>
#include <string>
#include <vector>
namespace dt::df
{
using NodeId = int;
using NodeKey = std::string;
using SlotPtr = std::shared_ptr<BaseSlot>;
using Slots = std::vector<SlotPtr>;
} // namespace dt::df
