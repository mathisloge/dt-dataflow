#include "simple_op.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace dt::df::op
{
static Slots makeInputs(IGraphManager &graph_manager, const std::string &in_a_name, const std::string &in_b_name)
{
    const auto &flot_fac = graph_manager.getSlotFactory("FloatingSlot");
    return Slots{flot_fac(graph_manager, SlotType::input, in_a_name, 0, SlotFieldVisibility::without_connection),
                 flot_fac(graph_manager, SlotType::input, in_b_name, 1, SlotFieldVisibility::without_connection)};
}
static Slots makeOutput(IGraphManager &graph_manager, const std::string &out_res_name)
{
    const auto &flot_fac = graph_manager.getSlotFactory("FloatingSlot");
    return Slots{flot_fac(graph_manager, SlotType::output, out_res_name, 0, SlotFieldVisibility::without_connection)};
}

SimpleOp::SimpleOp(IGraphManager &graph_manager,
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

SimpleOp::SimpleOp(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode(graph_manager, json)
{
    initSlots();
}

void SimpleOp::initSlots()
{
    result_slot_ = std::dynamic_pointer_cast<NumberSlot>(outputByLocalId(0));

    inputByLocalId(0)->subscribe([this](const BaseSlot *slot) {
        auto in_slot = dynamic_cast<const NumberSlot *>(slot);
        if (in_slot)
        {
            in_a_ = in_slot->value();
            setResult(calc(in_a_, in_b_));
        }
    });
    inputByLocalId(1)->subscribe([this](const BaseSlot *slot) {
        auto in_slot = dynamic_cast<const NumberSlot *>(slot);
        if (in_slot)
        {
            in_b_ = in_slot->value();
            setResult(calc(in_a_, in_b_));
        }
    });
}

void SimpleOp::setResult(const double res)
{
    result_slot_->setValue(res);
}

SimpleOp::~SimpleOp()
{}
} // namespace dt::df::operators
