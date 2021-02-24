#pragma once
#include "base_slot.hpp"
#include "any_slot.hpp"
namespace dt::df
{
class DTDFCORE_EXPORT NumberSlot : public AnySlot
{
  public:
    using AnySlot::AnySlot;
    virtual void setValue(double value);
    virtual double value() const = 0;
    virtual void accept(const BaseSlot *slot) override;
    virtual bool canConnect(const BaseSlot *const slot) const override;
    virtual ~NumberSlot();

  protected:
    virtual void accept(double value) = 0;
};
} // namespace dt::df
