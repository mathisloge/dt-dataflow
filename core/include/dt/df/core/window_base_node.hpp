#pragma once
#include <memory>
#include "base_node.hpp"

namespace dt::df::core
{
class DTDFCORE_EXPORT WindowBaseNode : public BaseNode
{
  public:
    WindowBaseNode(IGraphManager &graph_manager,
                   const NodeKey &key,
                   const std::string &node_title,
                   const std::string &window_title);
    virtual void render() override;
    virtual void init(core::IGraphManager &graph_manager) override;
    virtual void evaluate() override;
    virtual ~WindowBaseNode();

  protected:
    void setWindowFlags(int window_flags);
    int getWindowFlags() const;
    virtual void drawWindow() = 0;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace dt::df::core
