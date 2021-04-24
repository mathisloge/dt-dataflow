#pragma once
#include "base_node.hpp"

namespace dt::df
{
class DTDFCORE_EXPORT WindowNode : public BaseNode
{

  public:
    WindowNode(IGraphManager &graph_manager,
               const NodeKey &key,
               const std::string &node_title,
               const std::string &window_title,
               Slots &&inputs,
               Slots &&outputs);
    WindowNode(IGraphManager &graph_manager, const nlohmann::json &json);
    virtual void render() override;
    virtual void calculate() override;
    virtual ~WindowNode();

  protected:
    void setWindowFlags(int window_flags);
    int getWindowFlags() const;
    virtual void drawWindow() = 0;

  private:
    class Impl;
    Impl *impl_;
};
} // namespace dt::df
