#pragma once
#include "core_slot.hpp"
#include "dtdfcore_export.h"
#include "flow_base_slot.hpp"
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

    const SlotMap &inputs() const;
    const SlotMap &outputs() const;
    SlotPtr inputs(const SlotId global_id) const;
    SlotPtr outputs(const SlotId global_id) const;
    SlotPtr inputByLocalId(const SlotId id) const;
    SlotPtr outputByLocalId(const SlotId id) const;

    /**
     * @brief will be called once after the creation.
     * @user create your desired input and output slots here. register them with addInput, addOutput
     */
    virtual void init(core::IGraphManager &graph_manager) = 0;

    /**
     * @brief do the heavy computation etc. here.
     *
     */
    virtual void evaluate() = 0;
    /**
     * @brief will be called just before the node is removed from the graph.
     * @user close any connections and threads here.
     *
     */
    virtual void shutdown();

    /**
     * @brief only called if the graph is visibile
     * use @see renderCustomContent() to render some custom content into the node
     */
    virtual void render();
    void setPosition(int x, int y, bool is_screen_coords);

    /**
     * @brief normally a noop function. If your node normally don't republish the values, use this function to set
     * values again, so that connected nodes get the value of your node.
     */
    virtual void onConnect();
    virtual void beforeDisconnect();

  protected:
    /**
     * @brief
     * @attention all inputs registered outside of the @see init() function wont be used.
     */
    void addInput(const SlotPtr &slot);
    SlotPtr addInput(IGraphManager &graph_manager,
                     const SlotKey &slot_key,
                     const SlotName &slot_name,
                     const SlotId local_id);
    void addInputFlow(IGraphManager &graph_manager);
    /**
     * @brief
     * @attention all outputs registered outside of the @see init() function wont be used.
     */
    void addOutput(const SlotPtr &slot);
    SlotPtr addOutput(IGraphManager &graph_manager,
                      const SlotKey &slot_key,
                      const SlotName &slot_name,
                      const SlotId local_id);
    void addOutputFlow(IGraphManager &graph_manager);
    SlotFlowPtr addCustomOutputFlow(IGraphManager &graph_manager, const SlotName &slot_name, const SlotId local_id);

    virtual void renderCustomContent();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace dt::df::core
