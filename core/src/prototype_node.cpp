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
} // namespace dt::df::core
