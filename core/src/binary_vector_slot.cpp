#include "dt/df/core/binary_vector_slot.hpp"
#include <iostream>
#include <imgui.h>
namespace dt::df
{
void BinaryVectorSlot::setValue(Type value)
{
    accept(value);
    valueChanged();
}

void BinaryVectorSlot::accept(const BaseSlot *slot)
{
    auto input_slot = dynamic_cast<const BinaryVectorSlot *>(slot);
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
    return any.type() == typeid(BinaryVectorSlot::Type);
}
bool BinaryVectorSlot::canConnect(const BaseSlot *const slot) const
{
    if (dynamic_cast<const BinaryVectorSlot *const>(slot))
        return true;
    if (AnySlot::canConnect(slot))
    {
        auto any_input = dynamic_cast<const AnySlot *const>(slot);
        const auto &any_value = any_input->anyValue();
        return can_cast(any_value);
    }
    return false;
}

BinaryVectorSlot::~BinaryVectorSlot()
{}
} // namespace dt::df
