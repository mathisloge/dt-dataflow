#pragma once
#include "trigger_slot.hpp"
#include <imgui.h>
namespace dt::df
{

void TriggerSlot::notify()
{
    needsReevaluation();
}

} // namespace dt::df
