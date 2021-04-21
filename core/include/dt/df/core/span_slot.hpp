#pragma once
#include <span>
#include "base_slot.hpp"
namespace dt::df
{
/**
 * @brief
 * @todo this needs to be something more general. we could use a template for this one
 */
class DTDFCORE_EXPORT SpanSlot : public BaseSlot
{
  public:
    using Type = std::span<uint8_t>;

  public:
    using BaseSlot::BaseSlot;
    virtual void setValue(Type value);
    virtual Type value() const = 0;
    virtual void accept(const BaseSlot *slot) override;
    virtual bool canConnect(const BaseSlot *const slot) const override;
    virtual ~SpanSlot();

  protected:
    virtual void accept(Type value) = 0;
};
} // namespace dt::df
