#include "dt/df/core/flow_base_slot.hpp"

namespace dt::df::core
{
class FlowBaseSlot::Impl final
{
  public:
    const std::string key_;
    SignalT signal_;
};
FlowBaseSlot::FlowBaseSlot(
    IGraphManager &graph_manager, const SlotKey &key, const SlotType type, const SlotName &name, const SlotId local_id)
    : CoreSlot(graph_manager, key, type, name, local_id)
    , impl_{std::make_unique<Impl>()}
{}

void FlowBaseSlot::setValue()
{
    impl_->signal_();
}

boost::signals2::connection FlowBaseSlot::connectToNodeFnc(const typename SignalT::slot_type &slot)
{
    return impl_->signal_.connect(slot);
}

boost::signals2::connection FlowBaseSlot::connectTo(const std::shared_ptr<CoreSlot> &target_slot)
{
    std::shared_ptr<FlowBaseSlot> target_base = std::dynamic_pointer_cast<FlowBaseSlot>(target_slot);
    if (!target_base)
        throw std::invalid_argument{"cannot cast to type"}; //! \todo add key from core.
    return connectTo(target_base);
}

boost::signals2::connection FlowBaseSlot::connectTo(const std::shared_ptr<FlowBaseSlot> &target_slot)
{
    return impl_->signal_.connect(
        SignalT::slot_type(std::bind(&FlowBaseSlot::setValue, target_slot.get())).track_foreign(target_slot));
}

FlowBaseSlot::~FlowBaseSlot()
{}

} // namespace dt::df::core
