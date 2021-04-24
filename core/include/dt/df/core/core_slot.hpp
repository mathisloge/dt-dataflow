#pragma once
#include <memory>
#include <boost/signals2.hpp>
#include "dtdfcore_export.h"
#include "graph_manager.hpp"
#include "types.hpp"

namespace dt::df::core
{

class DTDFCORE_EXPORT CoreSlot
{
  public:
    explicit CoreSlot(IGraphManager &graph_manager,
                      const SlotKey &key,
                      const SlotType type,
                      const SlotName &name,
                      const SlotId local_id);
    CoreSlot(const CoreSlot &) = delete;
    CoreSlot &operator=(const CoreSlot &) = delete;
    virtual ~CoreSlot();

    const SlotKey &key() const;
    const SlotId id() const;
    const SlotId local_id() const;
    const SlotType type() const;
    const SlotName &name() const;
    bool canConnectTo(const SlotKey &target_key) const;

    //! @attention might throw invalid_argument if the connection cannot be established.
    virtual boost::signals2::connection connectTo(const std::shared_ptr<CoreSlot> &target_slot) = 0;

    // only used if the graph is visibile
    virtual void render();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace dt::df::core
