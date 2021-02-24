#pragma once
#include <dt/df/core/string_slot.hpp>
namespace dt::df
{
class StringSlotImpl final : public StringSlot
{
  public:
    static constexpr std::string_view kKey = "StringSlot";

  public:
    using StringSlot::StringSlot;
    const std::string &value() const override;

  private:
    void accept(const std::string &value) override;
    bool renderField() override;
    void renderValue() override;

  private:
    std::string value_;
};
} // namespace dt::df
