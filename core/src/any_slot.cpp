#include "dt/df/core/any_slot.hpp"
#include <imgui.h>
namespace dt::df
{
void AnySlot::setValue(const std::any &value)
{
    accept(value);
    valueChanged();
}

void AnySlot::accept(const BaseSlot *slot)
{
    auto input_slot = dynamic_cast<const AnySlot *>(slot);
    if (input_slot)
    {
        accept(input_slot->anyValue());
        valueChanged();
    }
}

bool AnySlot::canConnect(const BaseSlot *const slot) const
{
    return dynamic_cast<const AnySlot *const>(slot);
}

void AnySlot::render()
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

AnySlot::~AnySlot()
{}
} // namespace dt::df
