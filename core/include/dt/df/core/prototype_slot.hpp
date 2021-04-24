#pragma once
#include <exception>
#include <span>
#include "core_slot.hpp"
namespace dt::df::core
{

template <typename T>
class BaseSlot : public CoreSlot
{
  public:
    using SignalT = boost::signals2::signal<void(T)>;

  public:
    using CoreSlot::CoreSlot;

    // called from parent node
    void setValue(T value)
    {
        signal_(value);
    }

    // called to register node value setters
    boost::signals2::connection connectToNodeFnc(const typename SignalT::slot_type &slot)
    {
        return signal_.connect(slot);
    }

    boost::signals2::connection connectTo(const std::shared_ptr<CoreSlot> &target_slot) override
    {
        std::shared_ptr<BaseSlot<T>> target_base = std::dynamic_pointer_cast<BaseSlot<T>>(target_slot);
        if (!target_base)
            throw std::invalid_argument{"cannot cast to type"}; //! \todo add key from core.
        return connectTo(target_base);
    }

    boost::signals2::connection connectTo(const std::shared_ptr<BaseSlot<T>> &target_slot)
    {
        return signal_.connect(
            SignalT::slot_type(std::bind(&BaseSlot::inputSlot, target_slot.get(), std::placeholders::_1))
                .track_foreign(target_slot));
    }

    virtual ~BaseSlot()
    {}

  private:
    void inputSlot(T value)
    {
        signal_(value);
    }

  protected:
    const std::string key_;
    SignalT signal_;
};

} // namespace dt::df::core
