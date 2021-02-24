#include "string_slot.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>

namespace dt::df
{

const std::string &StringSlotImpl::value() const
{
    return value_;
}

void StringSlotImpl::accept(const std::string &value)
{
    value_ = value;
}

bool StringSlotImpl::renderField()
{
    return ImGui::InputText(name().c_str(), &value_);
}

void StringSlotImpl::renderValue()
{
    ImGui::TextUnformatted(value_.c_str());
}

} // namespace dt::df
