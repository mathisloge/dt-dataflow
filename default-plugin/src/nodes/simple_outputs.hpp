#pragma once
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/graph_manager.hpp>
#include "simple_output_builder.hpp"

namespace dt::df
{
DT_DF_BUILD_SIMPLE_O_NODE(IntNode)
DT_DF_BUILD_SIMPLE_O_NODE(BoolNode)
DT_DF_BUILD_SIMPLE_O_NODE(FloatingNode)
DT_DF_BUILD_SIMPLE_O_NODE(TextNode)

template <typename TNode>
void registerSimpleOutputNode(IGraphManager &graph)
{
    const std::string disp_name{std::string{"output/"} + std::string{TNode::kKey}};
    graph.registerNodeFactory(
        std::string{TNode::kKey},
        disp_name,
        [](IGraphManager &graph) { return std::make_shared<TNode>(graph); },
        [](IGraphManager &graph, const nlohmann::json &json) { return std::make_shared<TNode>(graph, json); });
}
} // namespace dt::df
