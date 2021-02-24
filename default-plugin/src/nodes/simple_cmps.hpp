#pragma once
#include "simple_cmp.hpp"
#include "simple_cmp_builder.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace dt::df::cmp
{
DT_DF_BUILD_SIMPLE_CMP(Less)
DT_DF_BUILD_SIMPLE_CMP(LEQ)
DT_DF_BUILD_SIMPLE_CMP(EQ)
DT_DF_BUILD_SIMPLE_CMP(NEQ)
DT_DF_BUILD_SIMPLE_CMP(GEQ)
DT_DF_BUILD_SIMPLE_CMP(Greater)

template <typename TNode>
void registerSimpleCmpNode(IGraphManager &graph)
{
    const std::string disp_name{std::string{"operators/logical/"} + std::string{TNode::kNodeName}};
    graph.registerNodeFactory(
        std::string{TNode::kNodeKey},
        disp_name,
        [](IGraphManager &graph) { return std::make_shared<TNode>(graph); },
        [](IGraphManager &graph, const nlohmann::json &json) { return std::make_shared<TNode>(graph, json); });
}

} // namespace dt::df::operators
