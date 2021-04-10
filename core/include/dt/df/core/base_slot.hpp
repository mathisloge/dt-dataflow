#pragma once
#include <memory>
#include <boost/signals2.hpp>
#include <nlohmann/json.hpp>
#include "dtdfcore_export.h"
#include "types.hpp"

namespace dt::df
{
class DTDFCORE_EXPORT BaseSlot
{
  public:
    using ValueChangedSignal = boost::signals2::signal<void(const BaseSlot *slot)>;

  public:
    BaseSlot(const SlotKey &key,
             IGraphManager &graph_manager,
             const SlotType type,
             const SlotName &name,
             const SlotId local_id = 0,
             SlotFieldVisibility visibility_rule = SlotFieldVisibility::without_connection);
    BaseSlot(const nlohmann::json &json);
    BaseSlot(const BaseSlot &) = delete;
    BaseSlot &operator=(const BaseSlot &) = delete;
    virtual ~BaseSlot();

    const SlotKey &key() const;
    SlotId id() const;
    SlotId localId() const;
    void localId(const SlotId id);
    SlotType type() const;
    const SlotName &name() const;

    virtual void connectEvent();
    virtual void disconnectEvent();
    // will be called as an input
    virtual void accept(const BaseSlot *slot) = 0;
    virtual bool canConnect(const BaseSlot *const slot) const = 0;
    virtual void render();

    void valueChanged();
    boost::signals2::connection subscribe(const ValueChangedSignal::slot_type &sub);
    bool hasConnection() const;
    SlotFieldVisibility visibility_rule() const;
    void visibility_rule(SlotFieldVisibility visibility_rule);

    virtual void to_json(nlohmann::json &j) const;

  protected:
    bool showField() const;

  private:
    class Impl;
    Impl *impl_;
};
} // namespace dt::df
