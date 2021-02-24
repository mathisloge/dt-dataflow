#include <dt/df/core/graph_manager.hpp>
#include "simple_op.hpp"
#include "simple_op_builder.hpp"
namespace dt::df::op
{
DT_DF_BUILD_SIMPLE_OP(Division)
DT_DF_BUILD_SIMPLE_OP(Multiplication)
DT_DF_BUILD_SIMPLE_OP(Addition)
DT_DF_BUILD_SIMPLE_OP(Subtraction)
DT_DF_BUILD_SIMPLE_OP(Modulo)
DT_DF_BUILD_SIMPLE_OP(Pow)

template <typename TNode>
void registerSimpleOpNode(IGraphManager &graph)
{
    const std::string disp_name{std::string{"operators/math/"} + std::string{TNode::kNodeName}};
    graph.registerNodeFactory(
        std::string{TNode::kNodeKey},
        disp_name,
        [](IGraphManager &graph) { return std::make_shared<TNode>(graph); },
        [](IGraphManager &graph, const nlohmann::json &json) { return std::make_shared<TNode>(graph, json); });
}
} // namespace dt::df::operators
