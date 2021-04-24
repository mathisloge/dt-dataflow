#pragma once
#include "core_slot.hpp"
#include "dtdfcore_export.h"
namespace dt::df::core
{
class DTDFCORE_EXPORT BaseNode
{
  public:
    explicit BaseNode(IGraphManager &graph_manager, const NodeKey &key, const std::string &title);
    BaseNode(const BaseNode &) = delete;
    BaseNode &operator=(const BaseNode &) = delete;
    virtual ~BaseNode();

    NodeId id() const;
    const NodeKey &key() const;
    const std::string &title() const;

    virtual void init() = 0;

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace dt::df::core
