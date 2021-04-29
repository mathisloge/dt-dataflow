#include "dt/df/core/base_node.hpp"
#include <imgui.h>
#include <imnodes.h>
#include "dt/df/core/flow_base_slot.hpp"

namespace dt::df::core
{
class BaseNode::Impl
{
  public:
    Impl(BaseNode &parent, IGraphManager &graph_manager, const NodeKey &key, const std::string &title)
        : parent_{parent}
        , id_{graph_manager.generateNodeId()}
        , key_{key}
        , title_{title}
        , position_was_updated_{false}
        , output_flow_{nullptr}
    {}

    SlotPtr findByGlobalId(const SlotMap &slots, const SlotId global_id)
    {
        auto slot_it = std::find_if(
            slots.begin(), slots.end(), [global_id](const auto &x) { return x.second->id() == global_id; });

        if (slot_it == slots.end())
            return nullptr;
        return slot_it->second;
    }

    void updatePosIfNeeded()
    {
        if (position_was_updated_)
        {
            if (is_screen_coords_)
                imnodes::SetNodeEditorSpacePos(id_, position_);
            else
                imnodes::SetNodeScreenSpacePos(id_, position_);
            position_was_updated_ = false;
        }
    }

    void setPosition(int x, int y, bool is_screen_coords = false)
    {
        position_ = {static_cast<float>(x), static_cast<float>(y)};
        is_screen_coords_ = is_screen_coords;
        position_was_updated_ = true;
    }

    void update()
    {
        parent_.evaluate();
        if (output_flow_)
            output_flow_->setValue();
    }
    BaseNode &parent_;
    const NodeId id_;
    const NodeKey key_;
    const std::string title_;

    SlotMap inputs_;
    SlotMap outputs_;

    std::shared_ptr<FlowBaseSlot> output_flow_;

    bool position_was_updated_;
    bool is_screen_coords_;
    ImVec2 position_;
};

BaseNode::BaseNode(IGraphManager &graph_manager, const NodeKey &key, const std::string &title)
    : impl_{std::make_unique<Impl>(*this, graph_manager, key, title)}
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

void BaseNode::addInput(const SlotPtr &slot)
{
    impl_->inputs_.emplace(slot->local_id(), slot);
    //! \todo maybe throw exception if the local id already exists?
}

SlotPtr BaseNode::addInput(IGraphManager &graph_manager,
                           const SlotKey &slot_key,
                           const SlotName &slot_name,
                           const SlotId local_id)
{
    const auto &fac = graph_manager.getSlotFactory(slot_key);
    auto p_slot = fac(graph_manager, SlotType::input, slot_name, local_id, SlotFieldVisibility::always);
    addInput(p_slot);
    return p_slot;
}

void BaseNode::addInputFlow(IGraphManager &graph_manager)
{
    std::dynamic_pointer_cast<FlowBaseSlot>(addInput(graph_manager, "FlowSlot", "in flow", -1))
        ->connectToNodeFnc(std::bind(&BaseNode::Impl::update, impl_.get()));
}

void BaseNode::addOutput(const SlotPtr &slot)
{
    impl_->outputs_.emplace(slot->local_id(), slot);
}

SlotPtr BaseNode::addOutput(IGraphManager &graph_manager,
                            const SlotKey &slot_key,
                            const SlotName &slot_name,
                            const SlotId local_id)
{
    const auto &fac = graph_manager.getSlotFactory(slot_key);
    auto p_slot = fac(graph_manager, SlotType::input, slot_name, local_id, SlotFieldVisibility::always);
    addOutput(p_slot);
    return p_slot;
}

const SlotMap &BaseNode::inputs() const
{
    return impl_->inputs_;
}
const SlotMap &BaseNode::outputs() const
{
    return impl_->outputs_;
}

void BaseNode::addOutputFlow(IGraphManager &graph_manager)
{
    impl_->output_flow_ = std::dynamic_pointer_cast<FlowBaseSlot>(addOutput(graph_manager, "FlowSlot", "out flow", -1));
}

SlotPtr BaseNode::inputs(const SlotId global_id) const
{
    return impl_->findByGlobalId(impl_->inputs_, global_id);
}
SlotPtr BaseNode::outputs(const SlotId global_id) const
{
    return impl_->findByGlobalId(impl_->outputs_, global_id);
}

SlotPtr BaseNode::inputByLocalId(const SlotId id) const
{
    auto slot_it = impl_->inputs_.find(id);
    if (slot_it == impl_->inputs_.end())
        return nullptr;
    return slot_it->second;
}
SlotPtr BaseNode::outputByLocalId(const SlotId id) const
{
    auto slot_it = impl_->outputs_.find(id);
    if (slot_it == impl_->outputs_.end())
        return nullptr;
    return slot_it->second;
}

void BaseNode::render()
{
    impl_->updatePosIfNeeded();

    imnodes::BeginNode(impl_->id_);
    imnodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(impl_->title_.c_str());
    imnodes::EndNodeTitleBar();

    for (auto &slot : impl_->inputs_)
    {
        imnodes::BeginInputAttribute(slot.second->id());
        slot.second->render();
        imnodes::EndInputAttribute();
    }

    renderCustomContent();

    for (auto &slot : impl_->outputs_)
    {
        imnodes::BeginOutputAttribute(slot.second->id());
        slot.second->render();
        imnodes::EndOutputAttribute();
    }
    imnodes::EndNode();
}

void BaseNode::renderCustomContent()
{}

void BaseNode::setPosition(int x, int y, bool is_screen_coords)
{
    impl_->setPosition(x, y, is_screen_coords);
}

void BaseNode::shutdown()
{}
} // namespace dt::df::core
