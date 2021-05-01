#include "dt/df/core/base_node.hpp"
#include <imgui.h>
#include <imnodes.h>
#include "dt/df/core/flow_base_slot.hpp"

namespace dt::df::core
{
class BaseNode::Impl
{
  public:
    Impl(BaseNode &parent)
        : parent_{parent}
        , output_flow_{nullptr}
    {}
    void update()
    {
        parent_.evaluate();
        if (output_flow_)
            output_flow_->setValue();
    }
    BaseNode &parent_;
    std::shared_ptr<FlowBaseSlot> output_flow_;
};

BaseNode::BaseNode(IGraphManager &graph_manager, const NodeKey &key, const std::string &title)
    : CoreNode{graph_manager, key}
    , UiNode{*this, title}
    , impl_{std::make_unique<Impl>(*this)}
{}

BaseNode::~BaseNode()
{}

SlotPtr BaseNode::addInput(IGraphManager &graph_manager,
                           const SlotKey &slot_key,
                           const SlotName &slot_name,
                           const SlotId local_id)
{
    const auto &fac = graph_manager.getSlotFactory(slot_key);
    auto p_slot = fac(graph_manager, SlotType::input, slot_name, local_id, SlotFieldVisibility::always);
    CoreNode::addInput(p_slot);
    return p_slot;
}

void BaseNode::addInputFlow(IGraphManager &graph_manager)
{
    std::dynamic_pointer_cast<FlowBaseSlot>(addInput(graph_manager, "FlowSlot", "in flow", -1))
        ->connectToNodeFnc(std::bind(&BaseNode::Impl::update, impl_.get()));
}

SlotPtr BaseNode::addOutput(IGraphManager &graph_manager,
                            const SlotKey &slot_key,
                            const SlotName &slot_name,
                            const SlotId local_id)
{
    const auto &fac = graph_manager.getSlotFactory(slot_key);
    auto p_slot = fac(graph_manager, SlotType::input, slot_name, local_id, SlotFieldVisibility::always);
    CoreNode::addOutput(p_slot);
    return p_slot;
}

void BaseNode::addOutputFlow(IGraphManager &graph_manager)
{
    impl_->output_flow_ = addCustomOutputFlow(graph_manager, "out flow", -1);
}

SlotFlowPtr BaseNode::addCustomOutputFlow(IGraphManager &graph_manager,
                                          const SlotName &slot_name,
                                          const SlotId local_id)
{
    return std::static_pointer_cast<FlowBaseSlot>(addOutput(graph_manager, "FlowSlot", slot_name, local_id));
}

void BaseNode::onConnect()
{}

void BaseNode::beforeDisconnect()
{}

void BaseNode::shutdown()
{}
} // namespace dt::df::core
