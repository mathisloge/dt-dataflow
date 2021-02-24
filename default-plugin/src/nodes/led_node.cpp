#include "led_node.hpp"
#include <dt/df/core/graph_manager.hpp>
#include <dt/df/core/value_less_slot.hpp>
namespace dt::df
{
static Slots createInputs(IGraphManager &graph_manager);
LedNode::LedNode(IGraphManager &graph_manager)
    : BaseNode{graph_manager, kKey, kName, createInputs(graph_manager), Slots{}}
    , is_on_{false}
    , color_{0.f, 1.f, 0.f, 1.f}
{
    initSlots();
}
LedNode::LedNode(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode{graph_manager, json}
    , is_on_{false}
    , color_{0.f, 1.f, 0.f, 1.f}
{
    initSlots();
}

void LedNode::renderCustomContent()
{
    const ImVec2 p = ImGui::GetCursorScreenPos();
    const float size = 36.f;
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    const auto pos = ImVec2{p.x + size * 0.5f, p.y + size * 0.5f};
    if (is_on_)
        draw_list->AddCircle(pos, size * 0.5f, color_);
    else
        draw_list->AddCircleFilled(pos, size * 0.5f, color_);
    ImGui::Dummy({size, size});
}

void LedNode::toggle()
{
    is_on_ = !is_on_;
}

void LedNode::initSlots()
{
    inputByLocalId(0)->subscribe([this](auto) { toggle(); });
}

Slots createInputs(IGraphManager &graph_manager)
{
    try
    {
        return Slots{graph_manager.getSlotFactory("TriggerSlot")(
            graph_manager, SlotType::input, "toggle", 0, SlotFieldVisibility::without_connection)};
    }
    catch (...)
    {}
    return Slots{};
}
} // namespace dt::df
