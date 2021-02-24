#pragma once
#include <dt/df/core/number_slot.hpp>
namespace dt::df
{
class IntSlot final : public NumberSlot
{
  public:
    static constexpr std::string_view kKey = "IntSlot";

  public:
    using NumberSlot::NumberSlot;
    const std::any &anyValue() const override;
    double value() const override;
    int valueInt() const;
    ~IntSlot() = default;

  private:
    void accept(int value);
    void accept(double value) override;
    void accept(const std::any &value) override;
    bool renderField() override;
    void renderValue() override;

  private:
    int value_ = 0;
    std::any any_value_;
};
} // namespace dt::df
