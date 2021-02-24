#include "dt/df/core/any_slot.hpp"
#include <imgui.h>
namespace dt::df
{
void AnySlot::setValue(const std::any &value)
{
    accept(value);
    needsReevaluation();
}

void AnySlot::accept(const BaseSlot *slot)
{
    auto input_slot = dynamic_cast<const AnySlot *>(slot);
    if (input_slot)
    {
        accept(input_slot->anyValue());
        needsReevaluation();
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
            needsReevaluation();
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
