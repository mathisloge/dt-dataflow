#pragma once
#include "../core/base_node.hpp"
#include "../core/base_slot.hpp"
namespace dt::df
{
template <typename T>
class SimpleOutputNode : public core::BaseNode
{
  public:
    using SlotDataT = const T &;
    using DataOutT = core::BaseSlot<SlotDataT>;
    using DataOutPtrT = std::shared_ptr<DataOutT>;

    explicit SimpleOutputNode(core::IGraphManager &graph_manager, const NodeKey &key, const std::string &title)
        : BaseNode(graph_manager, key, title)
        , output_slot_{nullptr}
    {}

    virtual void evaluate()
    {}

    std::shared_ptr<DataOutT> registerInput(core::IGraphManager &graph_manager,
                                               const SlotKey &slot_key,
                                               const SlotName &slot_name,
                                               const SlotId local_id)
    {
        return std::dynamic_pointer_cast<DataOutT>(addInput(graph_manager, slot_key, slot_name, local_id));
    }

    std::shared_ptr<DataOutT> registerOutput(core::IGraphManager &graph_manager,
                                                const SlotKey &slot_key,
                                                const SlotName &slot_name,
                                                const SlotId local_id)
    {
        return std::dynamic_pointer_cast<DataOutT>(addOutput(graph_manager, slot_key, slot_name, local_id));
    }

    virtual void onConnect()
    {
        output_slot_->setValue(value_);
    }

  protected:
    T value_;
    DataOutPtrT output_slot_;
};
} // namespace dt::df
