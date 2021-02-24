#pragma once
#include <dt/df/core/number_slot.hpp>
namespace dt::df
{
class FloatingSlot final : public NumberSlot
{
  public:
    static constexpr std::string_view kKey = "FloatingSlot";

  public:
    using NumberSlot::NumberSlot;
    const std::any &anyValue() const override;
    double value() const override;
    ~FloatingSlot() = default;

  private:
    void accept(double value) override;
    void accept(const std::any &value) override;

    bool renderField() override;
    void renderValue() override;

  private:
    double value_ = 0;
    std::any any_value_;
};
} // namespace dt::df
