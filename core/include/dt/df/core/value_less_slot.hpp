#pragma once
#include "base_slot.hpp"
namespace dt::df
{
class DTDFCORE_EXPORT ValueLessSlot : public BaseSlot
{
  public:
    using BaseSlot::BaseSlot;
    virtual void accept(const BaseSlot *slot) override;
    virtual bool canConnect(const BaseSlot *const slot) const override;
    virtual void render() override;
    virtual void notify() = 0;
    virtual ~ValueLessSlot();
};
} // namespace dt::df
