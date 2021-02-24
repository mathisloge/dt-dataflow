#pragma once
#include "types.hpp"
namespace dt::df
{
class IGraphManager
{

  public:
    IGraphManager() = default;

    virtual void registerNodeFactory(const NodeKey &key,
                                     const std::string &node_display_name,
                                     NodeFactory &&factory,
                                     NodeDeserializationFactory &&deser_factory) = 0;
    virtual void registerSlotFactory(const SlotKey &key,
                                     SlotFactory &&factory,
                                     SlotDeserializationFactory &&deser_factory) = 0;
    virtual const SlotFactory &getSlotFactory(const SlotKey &key) const = 0;
    virtual const SlotDeserializationFactory &getSlotDeserFactory(const SlotKey &key) const = 0;

    virtual NodeId generateNodeId() = 0;
    virtual SlotId generateSlotId() = 0;

    virtual bool registerSlot(const NodeId node_id, const SlotId slot_id, const SlotType type) = 0;
    virtual bool unregisterSlot(const NodeId node_id, const SlotId slot_id) = 0;

    virtual ~IGraphManager() = default;

    IGraphManager(const IGraphManager &) = delete;
    IGraphManager &operator=(const IGraphManager &) = delete;
};
} // namespace dt::df
