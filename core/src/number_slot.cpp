#include "dt/df/core/number_slot.hpp"
#include <imgui.h>
namespace dt::df
{
void NumberSlot::setValue(double value)
{
    accept(value);
    needsReevaluation();
}

void NumberSlot::accept(const BaseSlot *slot)
{
    auto input_slot = dynamic_cast<const NumberSlot *>(slot);
    if (input_slot)
    {
        accept(input_slot->value());
        needsReevaluation();
    }
}

bool NumberSlot::canConnect(const BaseSlot *const slot) const
{
    if (dynamic_cast<const NumberSlot *const>(slot))
        return true;
    if (AnySlot::canConnect(slot))
    {
        auto any_input = dynamic_cast<const AnySlot *const>(slot);
        try
        {
            const auto val = std::any_cast<double>(any_input->anyValue());
            // check if we can convert to double
            return true;
        }
        catch (const std::bad_any_cast &)
        {}
    }
    return false;
}

NumberSlot::~NumberSlot()
{}
} // namespace dt::df
