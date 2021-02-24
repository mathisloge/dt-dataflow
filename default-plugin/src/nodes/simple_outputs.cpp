#include "simple_outputs.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace dt::df
{
static Slots getOutputs(IGraphManager &graph_manager, const SlotKey &slot, const std::string &slot_title) noexcept
{
    try
    {
        return Slots{graph_manager.getSlotFactory(slot)(
            graph_manager, SlotType::output, slot_title, 0, SlotFieldVisibility::always)};
    }
    catch (...)
    {
        // todo: log error
    }
    return Slots{};
}

DT_DF_BUILD_SIMPLE_O_NODE_IMPL(BoolNode, Bool, BoolSlot, bool)
DT_DF_BUILD_SIMPLE_O_NODE_IMPL(IntNode, Int, IntSlot, int)
DT_DF_BUILD_SIMPLE_O_NODE_IMPL(FloatingNode, Floating, FloatingSlot, double)
DT_DF_BUILD_SIMPLE_O_NODE_IMPL(TextNode, Text, StringSlot, string)

} // namespace dt::df
