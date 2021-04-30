#include "dt/df/core/core_slot.hpp"
#include <imgui.h>
namespace dt::df::core
{
class CoreSlot::Impl
{
  public:
    explicit Impl(IGraphManager &graph_manager,
                  const SlotKey &key,
                  const SlotType type,
                  const SlotName &name,
                  const SlotId local_id)
        : key_{key}
        , id_{graph_manager.generateSlotId()}
        , local_id_{local_id}
        , type_{type}
        , name_{name}
    {}
    const SlotKey key_;
    const SlotId id_;
    const SlotId local_id_;
    const SlotType type_;
    const SlotName name_;
};

CoreSlot::CoreSlot(
    IGraphManager &graph_manager, const SlotKey &key, const SlotType type, const SlotName &name, const SlotId local_id)
    : impl_(std::make_unique<Impl>(graph_manager, key, type, name, local_id))
{}

CoreSlot::~CoreSlot()
{}

const SlotKey &CoreSlot::key() const
{
    return impl_->key_;
}

const SlotId CoreSlot::id() const
{
    return impl_->id_;
}
const SlotId CoreSlot::local_id() const
{
    return impl_->local_id_;
}
const SlotType CoreSlot::type() const
{
    return impl_->type_;
}
const SlotName &CoreSlot::name() const
{
    return impl_->name_;
}

bool CoreSlot::canConnectTo(const SlotKey &target_key) const
{
    return impl_->key_ == target_key;
}

void CoreSlot::render()
{
    ImGui::Text(impl_->name_.c_str());
}

} // namespace dt::df::core
