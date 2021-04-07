#include "dt/df/core/string_slot.hpp"
#include <imgui.h>
namespace dt::df
{
void StringSlot::setValue(const std::string &value)
{
    accept(value);
    valueChanged();
}

void StringSlot::accept(const BaseSlot *slot)
{
    auto input_slot = dynamic_cast<const StringSlot *>(slot);
    if (input_slot)
    {
        accept(input_slot->value());
        valueChanged();
    }
}

bool StringSlot::canConnect(const BaseSlot *const slot) const
{
    return dynamic_cast<const StringSlot *const>(slot);
}

void StringSlot::render()
{
    if (showField())
    {
        ImGui::SetNextItemWidth(100);
        if (renderField())
        {
            valueChanged();
        }
    }
    else
    {
        renderValue();
    }
}

StringSlot::~StringSlot()
{}
} // namespace dt::df
