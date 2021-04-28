#pragma once
#include <exception>
#include <span>
#include "core_slot.hpp"
namespace dt::df::core
{
class FlowBaseSlot : public CoreSlot
{
  public:
    using SignalT = boost::signals2::signal<void()>;

  public:
    explicit FlowBaseSlot(IGraphManager &graph_manager,
                          const SlotKey &key,
                          const SlotType type,
                          const SlotName &name,
                          const SlotId local_id);

    // called from parent node
    void setValue();
    // called to register node value setters
    boost::signals2::connection connectToNodeFnc(const typename SignalT::slot_type &slot);
    boost::signals2::connection connectTo(const std::shared_ptr<CoreSlot> &target_slot) override;
    boost::signals2::connection connectTo(const std::shared_ptr<FlowBaseSlot> &target_slot);
    virtual ~FlowBaseSlot();

  protected:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace dt::df::core
