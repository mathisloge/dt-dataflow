#include "dt/df/core/prototype_node.hpp"

namespace dt::df::core
{

class BaseNode::Impl
{
  public:
    Impl(IGraphManager &graph_manager, const NodeKey &key, const std::string &title)
        : id_{graph_manager.generateNodeId()}
        , key_{key}
        , title_{title}
    {}

    const NodeId id_;
    const NodeKey key_;
    const std::string title_;

    SlotMap inputs_;
    SlotMap outputs_;
};

BaseNode::BaseNode(IGraphManager &graph_manager, const NodeKey &key, const std::string &title)
    : impl_{std::make_unique<Impl>(graph_manager, key, title)}
{}

BaseNode::~BaseNode()
{}

NodeId BaseNode::id() const
{
    return impl_->id_;
}
const NodeKey &BaseNode::key() const
{
    return impl_->key_;
}
const std::string &BaseNode::title() const
{
    return impl_->title_;
}

void BaseNode::addInput(const std::shared_ptr<CoreSlot> &slot)
{
    impl_->inputs_.emplace(slot->local_id(), slot);
    //! \todo maybe throw exception if the local id already exists?
}

void BaseNode::addOutput(const std::shared_ptr<CoreSlot> &slot)
{
    impl_->outputs_.emplace(slot->local_id(), slot);
}

const SlotMap &BaseNode::inputs() const
{
    return impl_->inputs_;
}
const SlotMap &BaseNode::outputs() const
{
    return impl_->outputs_;
}

SlotPtrT BaseNode::inputByLocalId(const SlotId id) const
{
    auto slot_it = impl_->inputs_.find(id);
    if (slot_it == impl_->inputs_.end())
        return nullptr;
    return slot_it->second;
}
SlotPtrT BaseNode::outputByLocalId(const SlotId id) const
{
    auto slot_it = impl_->outputs_.find(id);
    if (slot_it == impl_->outputs_.end())
        return nullptr;
    return slot_it->second;
}

void BaseNode::shutdown()
{}
} // namespace dt::df::core
