#pragma once
#include <dt/df/core/base_node.hpp>
#include "../slots/bool_slot.hpp"
#include "../slots/trigger_slot.hpp"

namespace dt::df::cmp
{
class SimpleCmp : public BaseNode
{
  public:
    SimpleCmp(IGraphManager &graph_manager,
              const NodeKey &key,
              const std::string &title,
              const std::string &in_a_name,
              const std::string &in_b_name,
              const std::string &result_name);
    SimpleCmp(IGraphManager &graph_manager, const nlohmann::json &json);
    virtual ~SimpleCmp();

  protected:
    virtual bool cmp(const double a, const double b) const = 0;

  private:
    void initSlots();
    void setResult(const bool res);

  private:
    double in_a_;
    double in_b_;
    std::shared_ptr<BoolSlot> result_slot_;
    std::shared_ptr<TriggerSlot> true_slot_;
    std::shared_ptr<TriggerSlot> false_slot_;
};
} // namespace dt::df::operators
