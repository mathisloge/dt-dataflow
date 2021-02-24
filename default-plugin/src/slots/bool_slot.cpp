#pragma once
#include "bool_slot.hpp"
#include <imgui.h>

namespace dt::df
{
void BoolSlot::setValue(bool value)
{
    accept(value);
    needsReevaluation();
}

const std::any &BoolSlot::anyValue() const
{
    return any_value_;
}

double BoolSlot::value() const
{
    return value_;
}

bool BoolSlot::valueBool() const
{
    return value_;
}

void BoolSlot::accept(bool value)
{
    value_ = value;
    any_value_ = std::make_any<bool>(value_);
}

void BoolSlot::accept(double value)
{
    accept(static_cast<bool>(value));
}

void BoolSlot::accept(const std::any &value)
{
    try
    {
        accept(std::any_cast<bool>(value));
    }
    catch (std::bad_any_cast &)
    {
        // todo log.
    }
}

bool BoolSlot::renderField()
{
    if (ImGui::Checkbox(name().c_str(), &value_))
    {
        any_value_ = std::make_any<bool>(value_);
        return true;
    }
    return false;
}

void BoolSlot::renderValue()
{
    ImGui::Value(name().c_str(), value_);
}
} // namespace dt::df
