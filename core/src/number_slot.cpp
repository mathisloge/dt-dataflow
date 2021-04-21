#include "dt/df/core/number_slot.hpp"
#include <iostream>
#include <imgui.h>
namespace dt::df
{
void NumberSlot::setValue(double value)
{
    accept(value);
    valueChanged();
}

void NumberSlot::accept(const BaseSlot *slot)
{
    auto input_slot = dynamic_cast<const NumberSlot *>(slot);
    if (input_slot)
    {
        accept(input_slot->value());
        valueChanged();
        return;
    }
    AnySlot::accept(slot);
}

static bool can_cast(const std::any &any)
{
    if (!any.has_value())
        return false;
    const auto &type = any.type();
    if (type == typeid(int) || type == typeid(bool) || type == typeid(float) || type == typeid(double) ||
        type == typeid(long) || type == typeid(char) || type == typeid(long long))
        return true;
    return false;
}
bool NumberSlot::canConnect(const BaseSlot *const slot) const
{
    if (dynamic_cast<const NumberSlot *const>(slot))
        return true;
    if (AnySlot::canConnect(slot))
    {
        // we don't need to check for nullptr since AnySlot::canConnect checks.
        auto any_input = dynamic_cast<const AnySlot *const>(slot);
        const auto &any_value = any_input->anyValue();
        return can_cast(any_value);
    }
    return false;
}

NumberSlot::~NumberSlot()
{}
} // namespace dt::df
