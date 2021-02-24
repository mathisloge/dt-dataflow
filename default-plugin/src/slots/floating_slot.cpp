#pragma once
#include "floating_slot.hpp"
#include <imgui.h>
namespace dt::df
{

double FloatingSlot::value() const
{
    return value_;
}

const std::any &FloatingSlot::anyValue() const
{
    return any_value_;
}

void FloatingSlot::accept(double value)
{
    value_ = value;
    any_value_ = std::make_any<double>(value_);
}

void FloatingSlot::accept(const std::any &value)
{
    try
    {
        accept(std::any_cast<double>(value));
    }
    catch (std::bad_any_cast &)
    {
        // todo log.
    }
}

bool FloatingSlot::renderField()
{
    if (ImGui::InputDouble(name().c_str(), &value_))
    {
        accept(value_);
        return true;
    }
    return false;
}

void FloatingSlot::renderValue()
{
    ImGui::Value(name().c_str(), static_cast<float>(value_));
}
} // namespace dt::df
