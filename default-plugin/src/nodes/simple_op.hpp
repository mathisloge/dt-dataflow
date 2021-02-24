#pragma once
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/number_slot.hpp>

namespace dt::df::op
{
class SimpleOp : public BaseNode
{
  public:
    SimpleOp(IGraphManager &graph_manager,
             const NodeKey &key,
             const std::string &title,
             const std::string &in_a_name,
             const std::string &in_b_name,
             const std::string &result_name = "result");
    SimpleOp(IGraphManager &graph_manager, const nlohmann::json &json);
    virtual ~SimpleOp();

  protected:
    virtual double calc(const double a, const double b) const = 0;

  private:
    void initSlots();
    void setResult(const double res);

  private:
    double in_a_;
    double in_b_;
    std::shared_ptr<NumberSlot> result_slot_;
};
} // namespace dt::df::operators
