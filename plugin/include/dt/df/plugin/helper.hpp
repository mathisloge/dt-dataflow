#pragma once
#include <dt/df/core/base_slot.hpp>
namespace dt::df::plugin
{

template <typename TDatatype>
void registerBaseSlot(core::IGraphManager &graph, const SlotKey &key)
{
    using SlotDefT = core::BaseSlot<TDatatype>;
    graph.registerSlotFactory(
        key,
        [key](core::IGraphManager &graph, SlotType type, const SlotName &name, SlotId local, SlotFieldVisibility vis) {
            return std::make_shared<SlotDefT>(graph, key, type, name, local);
        },
        [](const nlohmann::json &json) { return /*std::make_shared<TSlot>(json);*/ nullptr; });
}

template <typename TNode>
void registerNode(core::IGraphManager &graph, const std::string &group)
{
    graph.registerNodeFactory(
        TNode::kKey,
        group + std::string{TNode::kName},
        [](core::IGraphManager &graph) { return std::make_shared<TNode>(graph); },
        [](core::IGraphManager &graph, const nlohmann::json &json) {
            return /*std::make_shared<TNode>(graph, json);*/ nullptr;
        });
}
} // namespace dt::df::plugin
