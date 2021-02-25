#pragma once
#include "any_slot.hpp"
#include "base_slot.hpp"
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

  public:
    template <typename T>
    T implicit_any_cast(const std::any &any)
    {
        const auto &type = any.type();
        if (type == typeid(int))
            return static_cast<T>(std::any_cast<int>(any));
        else if (type == typeid(double))
            return static_cast<T>(std::any_cast<double>(any));
        else if (type == typeid(bool))
            return static_cast<T>(std::any_cast<bool>(any));

        return std::any_cast<T>(any);
    }
};
} // namespace dt::df
