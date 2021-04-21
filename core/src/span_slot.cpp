#include "dt/df/core/span_slot.hpp"
#include <iostream>
#include <imgui.h>
namespace dt::df
{
void SpanSlot::setValue(Type value)
{
    accept(value);
    valueChanged();
}

void SpanSlot::accept(const BaseSlot *slot)
{
    auto input_slot = dynamic_cast<const SpanSlot *>(slot);
    if (input_slot)
    {
        accept(input_slot->value());
        valueChanged();
        return;
    }
}

bool SpanSlot::canConnect(const BaseSlot *const slot) const
{
    if (dynamic_cast<const SpanSlot *const>(slot))
        return true;
    return false;
}

SpanSlot::~SpanSlot()
{}
} // namespace dt::df
