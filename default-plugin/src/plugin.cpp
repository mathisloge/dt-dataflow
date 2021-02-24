#include <Corrade/PluginManager/AbstractManager.h>
#include <dt/df/plugin/plugin.hpp>
#include <imnodes.h>
#include "nodes/led_node.hpp"
#include "nodes/simple_cmps.hpp"
#include "nodes/simple_ops.hpp"
#include "nodes/simple_outputs.hpp"
#include "nodes/timer_node.hpp"
#include "slots/bool_slot.hpp"
#include "slots/floating_slot.hpp"
#include "slots/int_slot.hpp"
#include "slots/string_slot.hpp"
#include "slots/trigger_slot.hpp"

namespace dt::df::plugin
{
template <typename TSlot>
void registerSlot(IGraphManager &graph)
{
    graph.registerSlotFactory(
        TSlot::kKey,
        [](IGraphManager &graph, SlotType type, const SlotName &name, SlotId local, SlotFieldVisibility vis) {
            return std::make_shared<TSlot>(TSlot::kKey, graph, type, name, local, vis);
        },
        [](const nlohmann::json &json) { return std::make_shared<TSlot>(json); });
}

template <typename TNode>
void registerNode(IGraphManager &graph, const std::string &group)
{
    graph.registerNodeFactory(
        TNode::kKey,
        group + std::string{TNode::kName},
        [](IGraphManager &graph) { return std::make_shared<TNode>(graph); },
        [](IGraphManager &graph, const nlohmann::json &json) { return std::make_shared<TNode>(graph, json); });
}
class DefaultPlugin final : public Plugin
{

  public:
    explicit DefaultPlugin(Corrade::PluginManager::AbstractManager &manager, const std::string &plugin)
        : Plugin{manager, plugin}
    {}

    void setup(ImGuiContext *imgui_ctx, imnodes::Context *imnodes_ctx)
    {
        ImGui::SetCurrentContext(imgui_ctx);
        imnodes::SetCurrentContext(imnodes_ctx);
    }
    void registerNodeFactories(IGraphManager &graph)
    {
        registerSimpleOutputNode<IntNode>(graph);
        registerSimpleOutputNode<BoolNode>(graph);
        registerSimpleOutputNode<FloatingNode>(graph);
        registerSimpleOutputNode<TextNode>(graph);

        cmp::registerSimpleCmpNode<cmp::EQ>(graph);
        cmp::registerSimpleCmpNode<cmp::GEQ>(graph);
        cmp::registerSimpleCmpNode<cmp::LEQ>(graph);
        cmp::registerSimpleCmpNode<cmp::Greater>(graph);
        cmp::registerSimpleCmpNode<cmp::Less>(graph);
        cmp::registerSimpleCmpNode<cmp::NEQ>(graph);

        op::registerSimpleOpNode<op::Addition>(graph);
        op::registerSimpleOpNode<op::Subtraction>(graph);
        op::registerSimpleOpNode<op::Division>(graph);
        op::registerSimpleOpNode<op::Modulo>(graph);
        op::registerSimpleOpNode<op::Multiplication>(graph);
        op::registerSimpleOpNode<op::Pow>(graph);

        registerNode<TimerNode>(graph, "utilities/");
        registerNode<LedNode>(graph, "utilities/");
    }
    void registerSlotFactories(IGraphManager &graph)
    {
        registerSlot<BoolSlot>(graph);
        registerSlot<FloatingSlot>(graph);
        registerSlot<IntSlot>(graph);
        registerSlot<StringSlotImpl>(graph);
        registerSlot<TriggerSlot>(graph);
    }
};
} // namespace dt::df::plugin

CORRADE_PLUGIN_REGISTER(DefaultPlugin, dt::df::plugin::DefaultPlugin, "de.mathisloge.dt.dataflow/1.0")
