#pragma once
#include "base_slot.hpp"
namespace dt::df
{
class DTDFCORE_EXPORT StringSlot : public BaseSlot
{
  public:
    using BaseSlot::BaseSlot;
    virtual void setValue(const std::string &value);
    virtual const std::string &value() const = 0;
    virtual void accept(const BaseSlot *slot) override;
    virtual bool canConnect(const BaseSlot *const slot) const override;
    virtual void render() override;
    virtual ~StringSlot();

  protected:
    virtual void accept(const std::string &value) = 0;
    virtual bool renderField() = 0;
    virtual void renderValue() = 0;
};
} // namespace dt::df
