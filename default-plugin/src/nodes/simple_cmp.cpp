#include "simple_cmp.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace dt::df::cmp
{
static Slots makeInputs(IGraphManager &graph_manager, const std::string &in_a_name, const std::string &in_b_name)
{
    const auto &flot_fac = graph_manager.getSlotFactory("FloatingSlot");
    return Slots{flot_fac(graph_manager, SlotType::input, in_a_name, 0, SlotFieldVisibility::without_connection),
                 flot_fac(graph_manager, SlotType::input, in_b_name, 1, SlotFieldVisibility::without_connection)};
}
static Slots makeOutput(IGraphManager &graph_manager, const std::string &out_res_name)
{
    const auto &bool_fac = graph_manager.getSlotFactory("BoolSlot");
    const auto &trigger_fac = graph_manager.getSlotFactory("TriggerSlot");
    return Slots{bool_fac(graph_manager, SlotType::output, out_res_name, 0, SlotFieldVisibility::never),
                 trigger_fac(graph_manager, SlotType::output, "true", 1, SlotFieldVisibility::never),
                 trigger_fac(graph_manager, SlotType::output, "false", 2, SlotFieldVisibility::never)};
}

SimpleCmp::SimpleCmp(IGraphManager &graph_manager,
                     const NodeKey &key,
                     const std::string &title,
                     const std::string &in_a_name,
                     const std::string &in_b_name,
                     const std::string &result_name)
    : BaseNode{graph_manager,
               key,
               title,
               makeInputs(graph_manager, in_a_name, in_b_name),
               makeOutput(graph_manager, result_name)}
{
    initSlots();
}

SimpleCmp::SimpleCmp(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode(graph_manager, json)
{
    initSlots();
}

void SimpleCmp::initSlots()
{
    result_slot_ = std::dynamic_pointer_cast<BoolSlot>(outputByLocalId(0));
    true_slot_ = std::dynamic_pointer_cast<TriggerSlot>(outputByLocalId(1));
    false_slot_ = std::dynamic_pointer_cast<TriggerSlot>(outputByLocalId(2));
    inputByLocalId(0)->subscribe([this](const BaseSlot *slot) {
        auto in_slot = dynamic_cast<const NumberSlot *>(slot);
        if (in_slot)
        {
            in_a_ = in_slot->value();
            setResult(cmp(in_a_, in_b_));
        }
    });
    inputByLocalId(1)->subscribe([this](const BaseSlot *slot) {
        auto in_slot = dynamic_cast<const NumberSlot *>(slot);
        if (in_slot)
        {
            in_b_ = in_slot->value();
            setResult(cmp(in_a_, in_b_));
        }
    });
}

void SimpleCmp::setResult(const bool res)
{
    const bool res_prev = result_slot_->valueBool();
    if (res_prev != res)
    {
        result_slot_->setValue(res);
        res ? true_slot_->notify() : false_slot_->notify();
    }
}

SimpleCmp::~SimpleCmp()
{}
} // namespace dt::df::operators
