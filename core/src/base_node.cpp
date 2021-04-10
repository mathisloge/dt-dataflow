#include "dt/df/core/base_node.hpp"
#include <imgui.h>
#include <imnodes.h>
#include "dt/df/core/base_slot.hpp"
#include "dt/df/core/calculate_slot.hpp"
#include "dt/df/core/graph_manager.hpp"
#include "dt/df/core/json.hpp"

using json = nlohmann::json;
namespace dt::df
{
static SlotPtr makeSlot(IGraphManager &graph_manager, const nlohmann::json &json)
{
    try
    {
        const auto &fac = graph_manager.getSlotDeserFactory(json.at("key"));
        return fac(json);
    }
    catch (...)
    {}
    return nullptr;
}
static Slots makeInputs(IGraphManager &graph_manager, const nlohmann::json &json)
{
    Slots slots;
    try
    {
        const auto &in_json = json.at("inputs");
        for (const auto &slot_j : in_json)
        {
            auto slot = makeSlot(graph_manager, slot_j);
            if (slot)
                slots.emplace_back(std::move(slot));
        }
    }
    catch (...)
    {}
    return slots;
}
static Slots makeOutput(IGraphManager &graph_manager, const nlohmann::json &json)
{
    Slots slots;
    try
    {
        const auto &out_json = json.at("outputs");
        for (const auto &slot_j : out_json)
        {
            auto slot = makeSlot(graph_manager, slot_j);
            if (slot)
                slots.emplace_back(std::move(slot));
        }
    }
    catch (...)
    {}
    return slots;
}
static std::shared_ptr<CalculateSlot> createInputFlow(IGraphManager &graph_manager, SlotType type)
{
    try
    {
        const auto &calc_slot = graph_manager.getSlotFactory(CalculateSlot::kKey);
        return std::static_pointer_cast<CalculateSlot>(calc_slot(graph_manager,
                                                                 type,
                                                                 type == SlotType::input ? "FlowInput" : "FlowOutput",
                                                                 graph_manager.generateSlotId(),
                                                                 SlotFieldVisibility::never));
    }
    catch (...)
    {}
    return nullptr;
}
static std::shared_ptr<CalculateSlot> createFlowJson(IGraphManager &graph_manager,
                                                     SlotType type,
                                                     const nlohmann::json &json)
{
    try
    {
        const auto &val = json.at(type == SlotType::input ? "input_flow" : "output_flow");
        auto slot = makeSlot(graph_manager, val);
        return std::dynamic_pointer_cast<CalculateSlot>(slot);
    }
    catch (...)
    {}
    return nullptr;
}
class BaseNode::Impl
{
  public:
    Impl(BaseNode &parent,
         const NodeId id,
         const NodeKey &key,
         const std::string &title,
         Slots &&inputs,
         Slots &&outputs,
         std::shared_ptr<CalculateSlot> input_flow,
         std::shared_ptr<CalculateSlot> output_flow)
        : parent_{parent}
        , id_{id}
        , key_{key}
        , title_{title}
        , inputs_{std::move(inputs)}
        , outputs_{std::move(outputs)}
        , input_flow_{input_flow}
        , output_flow_{output_flow}
        , position_was_updated_{false}
    {
        input_flow->subscribe(std::bind(&Impl::calculate, this, std::placeholders::_1));
    }

    void calculate(const BaseSlot *)
    {
        parent_.calculate();
        triggerFlow();
    }

    void calculateIfNoFlow()
    {
        if (!input_flow_->hasConnection())
        {
            calculate(nullptr);
        }
    }

    void triggerFlow()
    {
        output_flow_->valueChanged();
    }

    void to_json(nlohmann::json &j) const
    {
        j["id"] = id_;
        j["key"] = key_;
        j["title"] = title_;
        json input_slots = json::array();
        json output_slots = json::array();
        for (const auto &slot : inputs_)
        {
            json slot_val;
            slot->to_json(slot_val);
            input_slots.emplace_back(std::move(slot_val));
        }
        for (const auto &slot : outputs_)
        {
            json slot_val;
            slot->to_json(slot_val);
            output_slots.emplace_back(std::move(slot_val));
        }
        j["inputs"] = std::move(input_slots);
        j["outputs"] = std::move(output_slots);

        input_flow_->to_json(j["input_flow"]);
        output_flow_->to_json(j["output_flow"]);

        const auto position = imnodes::GetNodeEditorSpacePos(id_);
        j["position"] = {{"x", position.x}, {"y", position.y}};
    }

    void setPosition(int x, int y, bool is_screen_coords = false)
    {
        position_ = {static_cast<float>(x), static_cast<float>(y)};
        is_screen_coords_ = is_screen_coords;
        position_was_updated_ = true;
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

    template <class Predicate>
    static SlotPtr find(const Slots &slots, Predicate pred)
    {
        auto slot_it = std::find_if(slots.begin(), slots.end(), pred);

        if (slot_it == slots.end())
            return nullptr;
        return *slot_it;
    }

  private:
    BaseNode &parent_;
    const NodeId id_;
    const NodeKey key_;
    const std::string title_;
    const Slots inputs_;
    const Slots outputs_;
    std::shared_ptr<CalculateSlot> input_flow_;
    std::shared_ptr<CalculateSlot> output_flow_;

    bool position_was_updated_;
    bool is_screen_coords_;
    ImVec2 position_;

    friend BaseNode;
};

BaseNode::BaseNode(
    IGraphManager &graph_manager, const NodeKey &key, const std::string &title, Slots &&inputs, Slots &&outputs)
    : impl_{new BaseNode::Impl{*this,
                               graph_manager.generateNodeId(),
                               key,
                               title,
                               std::forward<Slots>(inputs),
                               std::forward<Slots>(outputs),
                               createInputFlow(graph_manager, SlotType::input),
                               createInputFlow(graph_manager, SlotType::output)}}
{}

BaseNode::BaseNode(IGraphManager &g, const nlohmann::json &json)
{
    try
    {
        impl_ = new BaseNode::Impl{*this,
                                   json.at("id"),
                                   json.at("key"),
                                   json.at("title"),
                                   makeInputs(g, json),
                                   makeOutput(g, json),
                                   createFlowJson(g, SlotType::input, json),
                                   createFlowJson(g, SlotType::output, json)};
        const auto &pos = json.at("position");
        impl_->setPosition(pos.at("x"), pos.at("y"));
    }
    catch (...)
    {}
}

const NodeKey &BaseNode::key() const
{
    return impl_->key_;
}

void BaseNode::calculateIfNoFlow()
{
    impl_->calculateIfNoFlow();
}

void BaseNode::triggerFlow()
{
    impl_->triggerFlow();
}

void BaseNode::render()
{
    impl_->updatePosIfNeeded();

    imnodes::BeginNode(impl_->id_);
    imnodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(impl_->title_.c_str());
    imnodes::EndNodeTitleBar();

    imnodes::BeginInputAttribute(impl_->input_flow_->id());
    impl_->input_flow_->render();
    imnodes::EndInputAttribute();

    for (auto &slot : impl_->inputs_)
    {
        imnodes::BeginInputAttribute(slot->id());
        slot->render();
        imnodes::EndInputAttribute();
    }

    renderCustomContent();

    imnodes::BeginOutputAttribute(impl_->output_flow_->id());
    impl_->output_flow_->render();
    imnodes::EndOutputAttribute();

    for (auto &slot : impl_->outputs_)
    {
        imnodes::BeginOutputAttribute(slot->id());
        slot->render();
        imnodes::EndOutputAttribute();
    }
    imnodes::EndNode();
}

void BaseNode::setPosition(int x, int y, bool is_screen_coords)
{
    impl_->setPosition(x, y, is_screen_coords);
}

void BaseNode::renderCustomContent()
{}

NodeId BaseNode::id() const
{
    return impl_->id_;
}

const Slots &BaseNode::inputs() const
{
    return impl_->inputs_;
}
const Slots &BaseNode::outputs() const
{
    return impl_->outputs_;
}

SlotPtr BaseNode::inputs(const SlotId id) const
{
    return impl_->find(impl_->inputs_, [id](const auto &slot) { return slot->id() == id; });
}
SlotPtr BaseNode::outputs(const SlotId id) const
{
    return impl_->find(impl_->outputs_, [id](const auto &slot) { return slot->id() == id; });
}

SlotPtr BaseNode::inputByLocalId(const SlotId id) const
{
    return impl_->find(impl_->inputs_, [id](const auto &slot) { return slot->localId() == id; });
}
SlotPtr BaseNode::outputByLocalId(const SlotId id) const
{
    return impl_->find(impl_->outputs_, [id](const auto &slot) { return slot->localId() == id; });
}

void BaseNode::to_json(nlohmann::json &j) const
{
    impl_->to_json(j);
}

BaseNode::~BaseNode()
{
    delete impl_;
}

} // namespace dt::df
