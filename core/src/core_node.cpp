#include "dt/df/core/core_node.hpp"
namespace dt::df::core
{
class CoreNode::Impl final
{
  public:
    Impl(IGraphManager &graph_manager, const NodeKey &key)
        : id_{graph_manager.generateNodeId()}
        , key_{key}
    {}

    SlotPtr findByGlobalId(const SlotMap &slots, const SlotId global_id)
    {
        auto slot_it = std::find_if(
            slots.begin(), slots.end(), [global_id](const auto &x) { return x.second->id() == global_id; });

        if (slot_it == slots.end())
            return nullptr;
        return slot_it->second;
    }

  public:
    const NodeId id_;
    const NodeKey key_;
    SlotMap inputs_;
    SlotMap outputs_;
};

CoreNode::CoreNode(IGraphManager &graph_manager, const NodeKey &key)
    : impl_{std::make_unique<Impl>(graph_manager, key)}
{}
CoreNode::~CoreNode()
{}

NodeId CoreNode::id() const
{
    return impl_->id_;
}
const NodeKey &CoreNode::key() const
{
    return impl_->key_;
}

const SlotMap &CoreNode::inputs() const
{
    return impl_->inputs_;
}
const SlotMap &CoreNode::outputs() const
{
    return impl_->outputs_;
}

SlotPtr CoreNode::inputs(const SlotId global_id) const
{
    return impl_->findByGlobalId(impl_->inputs_, global_id);
}
SlotPtr CoreNode::outputs(const SlotId global_id) const
{
    return impl_->findByGlobalId(impl_->outputs_, global_id);
}
SlotPtr CoreNode::inputByLocalId(const SlotId id) const
{
    auto slot_it = impl_->inputs_.find(id);
    if (slot_it == impl_->inputs_.end())
        return nullptr;
    return slot_it->second;
}
SlotPtr CoreNode::outputByLocalId(const SlotId id) const
{
    auto slot_it = impl_->outputs_.find(id);
    if (slot_it == impl_->outputs_.end())
        return nullptr;
    return slot_it->second;
}

void CoreNode::addInput(const SlotPtr &slot)
{
    impl_->inputs_.emplace(slot->local_id(), slot);
}
void CoreNode::addOutput(const SlotPtr &slot)
{
    impl_->outputs_.emplace(slot->local_id(), slot);
}

} // namespace dt::df::core
