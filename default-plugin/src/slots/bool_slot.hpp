#pragma once
#include <dt/df/core/number_slot.hpp>
namespace dt::df
{
class BoolSlot final : public NumberSlot
{
  public:
    static constexpr std::string_view kKey = "BoolSlot";

  public:
    using NumberSlot::NumberSlot;
    const std::any &anyValue() const override;
    double value() const override;
    bool valueBool() const;
    void setValue(bool value);
    ~BoolSlot() = default;

  private:
    void accept(bool value);
    void accept(double value) override;
    void accept(const std::any &value) override;
    bool renderField() override;
    void renderValue() override;

  private:
    bool value_ = false;
    std::any any_value_;
};
} // namespace dt::df
