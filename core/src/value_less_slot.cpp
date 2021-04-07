#include "dt/df/core/value_less_slot.hpp"
#include <imgui.h>

namespace dt::df
{

void ValueLessSlot::accept(const BaseSlot *slot)
{
    if (canConnect(slot))
    {
        valueChanged();
    }
}
bool ValueLessSlot::canConnect(const BaseSlot *const slot) const
{
    return dynamic_cast<const ValueLessSlot *const>(slot);
}

void ValueLessSlot::render()
{
    if (showField())
    {
        if (ImGui::SmallButton(name().c_str()))
            valueChanged();
    }
    else
    {
        ImGui::Text(name().c_str());
    }
}

ValueLessSlot::~ValueLessSlot()
{}

} // namespace dt::df
