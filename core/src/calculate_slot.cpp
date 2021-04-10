#include "dt/df/core/calculate_slot.hpp"

namespace dt::df
{

void CalculateSlot::accept(const BaseSlot *)
{
    valueChanged();
}
bool CalculateSlot::canConnect(const BaseSlot *const slot) const
{
    return dynamic_cast<const CalculateSlot *const>(slot) != nullptr;
}

} // namespace dt::df
