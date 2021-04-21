#pragma once
#include <vector>
#include "any_slot.hpp"
#include "base_slot.hpp"
namespace dt::df
{
class DTDFCORE_EXPORT BinaryVectorSlot : public AnySlot
{
  public:
    using Type = std::vector<uint8_t>;

  public:
    using AnySlot::AnySlot;
    virtual void setValue(Type value);
    virtual Type value() const = 0;
    virtual void accept(const BaseSlot *slot) override;
    virtual bool canConnect(const BaseSlot *const slot) const override;
    virtual ~BinaryVectorSlot();

  protected:
    virtual void accept(std::vector<uint8_t> value) = 0;
};
} // namespace dt::df
