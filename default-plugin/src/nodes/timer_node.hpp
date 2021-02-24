#pragma once
#include <memory>
#include <thread>
#include <boost/asio.hpp>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/number_slot.hpp>
#include <dt/df/core/value_less_slot.hpp>
namespace dt::df
{
class TimerNode final : public BaseNode
{
  public:
    static constexpr const char *kKey = "TimerNode";
    static constexpr const char *kName = "Timer";

  public:
    TimerNode(IGraphManager &graph_manager);
    TimerNode(IGraphManager &graph_manager, const nlohmann::json &);
    ~TimerNode();

  private:
    void setDelay(std::chrono::milliseconds delay);
    void wakeup(const boost::system::error_code &);
    void ioLoop();
    void initSlots();

  private:
    std::chrono::milliseconds delay_;
    bool run_;
    std::thread io_thread_;
    boost::asio::io_context io_ctx_;
    boost::asio::steady_timer timer_;

    std::shared_ptr<ValueLessSlot> output_;
};
} // namespace dt::df
