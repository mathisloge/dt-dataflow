#pragma once
#include "dtdfcore_export.h"
#include "graph_manager.hpp"

#include "core_slot.hpp"
#include "types.hpp"
namespace dt::df::core
{
class DTDFCORE_EXPORT CoreNode
{
  public:
    explicit CoreNode(IGraphManager &graph_manager, const NodeKey &key);
    CoreNode(const CoreNode &) = delete;
    CoreNode &operator=(const CoreNode &) = delete;
    virtual ~CoreNode();

    NodeId id() const;
    const NodeKey &key() const;

    const SlotMap &inputs() const;
    const SlotMap &outputs() const;
    SlotMap &inputs();
    SlotMap &outputs();

    SlotPtr inputs(const SlotId global_id) const;
    SlotPtr outputs(const SlotId global_id) const;
    SlotPtr inputByLocalId(const SlotId id) const;
    SlotPtr outputByLocalId(const SlotId id) const;

    void addInput(const SlotPtr &slot);
    void addOutput(const SlotPtr &slot);

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace dt::df::core
