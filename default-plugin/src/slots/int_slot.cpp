#pragma once
#include "int_slot.hpp"
#include <imgui.h>

namespace dt::df
{

double IntSlot::value() const
{
    return value_;
}

const std::any &IntSlot::anyValue() const
{
    return any_value_;
}

int IntSlot::valueInt() const
{
    return value_;
}

void IntSlot::accept(int value)
{
    value_ = value;
    any_value_ = std::make_any<bool>(value_);
}

void IntSlot::accept(double value)
{
    accept(static_cast<int>(value));
}
void IntSlot::accept(const std::any &value)
{
    try
    {
        accept(std::any_cast<int>(value));
    }
    catch (std::bad_any_cast &)
    {
        // todo log.
    }
}

bool IntSlot::renderField()
{
    return ImGui::InputInt(name().c_str(), &value_);
}
void IntSlot::renderValue()
{
    ImGui::Value(name().c_str(), value_);
}

} // namespace dt::df
