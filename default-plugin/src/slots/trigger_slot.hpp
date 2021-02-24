#pragma once
#include <dt/df/core/base_slot.hpp>
namespace dt::df
{
class TriggerSlot final : public BaseSlot
{
  public:
    static constexpr std::string_view kKey = "TriggerSlot";

  public:
    using BaseSlot::BaseSlot;
    void accept(const BaseSlot *slot) override;
    bool canConnect(const BaseSlot *const slot) const override;
    void render() override;
    void trigger();
    ~TriggerSlot() = default;
};
} // namespace dt::df
