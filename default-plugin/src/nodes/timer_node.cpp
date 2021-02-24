#include "timer_node.hpp"
#include <chrono>
#include <thread>
#include <dt/df/core/graph_manager.hpp>
#include <imgui.h>
using namespace std::chrono_literals;

namespace dt::df
{

static Slots createInputs(IGraphManager &graph_manager);
static Slots createOutputs(IGraphManager &graph_manager);
TimerNode::TimerNode(IGraphManager &graph_manager)
    : BaseNode{graph_manager, kKey, kName, createInputs(graph_manager), createOutputs(graph_manager)}
    , delay_{1s}
    , run_{true}
    , timer_{io_ctx_}
    , io_thread_{std::bind(&TimerNode::ioLoop, this)}

{
    initSlots();
}
TimerNode::TimerNode(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode{graph_manager, json}
    , delay_{1s}
    , run_{true}
    , timer_{io_ctx_}
    , io_thread_{std::bind(&TimerNode::ioLoop, this)}
{
    initSlots();
}

void TimerNode::setDelay(std::chrono::milliseconds delay)
{
    delay_ = delay;
    timer_.cancel();
}

void TimerNode::wakeup(const boost::system::error_code &ec)
{
    if (!run_)
        return;
    // only wait if the timer expired or the operation was canceled ( due to setDelay )
    if (ec == boost::system::errc::operation_canceled || timer_.expiry() <= std::chrono::steady_clock::now())
    {
        if (!ec)
            output_->notify();
        timer_.expires_after(delay_);
        timer_.async_wait(std::bind(&TimerNode::wakeup, this, std::placeholders::_1));
    }
}

void TimerNode::ioLoop()
{
    while (run_)
    {
        io_ctx_.run();
        // add a small amount of time. Sometimes calling run to fast will result in errors.
        if (run_)
            std::this_thread::sleep_for(delay_ > 10ms ? delay_ - 10ms : 10ms);
    }
}

void TimerNode::initSlots()
{
    auto input_ms = std::dynamic_pointer_cast<NumberSlot>(inputByLocalId(0));
    input_ms->subscribe([this](const BaseSlot *slot) {
        auto nb_slot = dynamic_cast<const NumberSlot *>(slot);
        setDelay(std::chrono::milliseconds(static_cast<int>(nb_slot->value())));
    });
    auto reset = std::dynamic_pointer_cast<ValueLessSlot>(inputByLocalId(1));
    reset->subscribe([this](const BaseSlot *slot) { setDelay(delay_); });

    output_ = std::dynamic_pointer_cast<ValueLessSlot>(outputByLocalId(0));

    timer_.expires_after(delay_);
    timer_.async_wait(std::bind(&TimerNode::wakeup, this, std::placeholders::_1));
}

TimerNode::~TimerNode()
{
    run_ = false;
    timer_.cancel();
    io_ctx_.stop();
    if (io_thread_.joinable())
        io_thread_.join();
}

Slots createInputs(IGraphManager &graph_manager)
{
    Slots slots;
    try
    {
        const auto &int_fac = graph_manager.getSlotFactory("IntSlot");
        const auto &trig_fac = graph_manager.getSlotFactory("TriggerSlot");

        slots.emplace_back(
            int_fac(graph_manager, SlotType::input, "millisecs.", 0, SlotFieldVisibility::without_connection));
        slots.emplace_back(
            trig_fac(graph_manager, SlotType::input, "reset", 1, SlotFieldVisibility::without_connection));
    }
    catch (...)
    {}

    return slots;
}
Slots createOutputs(IGraphManager &graph_manager)
{
    Slots slots;
    try
    {
        const auto &slot_fac = graph_manager.getSlotFactory("TriggerSlot");
        slots.emplace_back(slot_fac(graph_manager, SlotType::output, "trigger", 0, SlotFieldVisibility::never));
    }
    catch (...)
    {}
    return slots;
}

} // namespace dt::df
