#pragma once
#include <any>
#include "base_slot.hpp"
namespace dt::df
{
class DTDFCORE_EXPORT AnySlot : public BaseSlot
{
  public:
    using BaseSlot::BaseSlot;
    virtual void setValue(const std::any &value);
    virtual const std::any &anyValue() const = 0;
    virtual void accept(const BaseSlot *slot) override;
    //! child class should override this and test, if the value() return fits the expected type
    virtual bool canConnect(const BaseSlot *const slot) const override;
    virtual void render() override;
    virtual ~AnySlot();

  protected:
    virtual void accept(const std::any &value) = 0;
    virtual bool renderField() = 0;
    virtual void renderValue() = 0;
};
} // namespace dt::df
