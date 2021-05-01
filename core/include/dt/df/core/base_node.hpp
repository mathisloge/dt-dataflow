#pragma once
#include "core_node.hpp"
#include "core_slot.hpp"
#include "dtdfcore_export.h"
#include "flow_base_slot.hpp"
#include "ui_node.hpp"
namespace dt::df::core
{

class DTDFCORE_EXPORT BaseNode : public CoreNode, public UiNode
{
  public:
    explicit BaseNode(IGraphManager &graph_manager, const NodeKey &key, const std::string &title);
    virtual ~BaseNode();

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
    SlotPtr addInput(IGraphManager &graph_manager,
                     const SlotKey &slot_key,
                     const SlotName &slot_name,
                     const SlotId local_id);
    void addInputFlow(IGraphManager &graph_manager);
    /**
     * @brief
     * @attention all outputs registered outside of the @see init() function wont be used.
     */
    SlotPtr addOutput(IGraphManager &graph_manager,
                      const SlotKey &slot_key,
                      const SlotName &slot_name,
                      const SlotId local_id);
    void addOutputFlow(IGraphManager &graph_manager);
    SlotFlowPtr addCustomOutputFlow(IGraphManager &graph_manager, const SlotName &slot_name, const SlotId local_id);

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace dt::df::core
