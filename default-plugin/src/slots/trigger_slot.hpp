#pragma once
#include <dt/df/core/value_less_slot.hpp>
namespace dt::df
{
class TriggerSlot final : public ValueLessSlot
{
  public:
    static constexpr std::string_view kKey = "TriggerSlot";

  public:
    using ValueLessSlot::ValueLessSlot;
    void notify() override;
};
} // namespace dt::df
