#include <Corrade/PluginManager/AbstractManager.h>
#include <dt/df/plugin/plugin.hpp>
#include <imnodes.h>
#include "slots/bool_slot.hpp"
#include "slots/floating_slot.hpp"
#include "slots/int_slot.hpp"
#include "slots/string_slot.hpp"
#include "slots/trigger_slot.hpp"
namespace dt::df::plugin
{
template <typename TSlot>
void registerSlot(IGraphManager &graph)
{
    graph.registerSlotFactory(
        TSlot::kKey,
        [](IGraphManager &graph, SlotType type, const SlotName &name, SlotId local, SlotFieldVisibility vis) {
            return std::make_shared<TSlot>(TSlot::kKey, graph, type, name, local, vis);
        },
        [](const nlohmann::json &json) { return std::make_shared<TSlot>(json); });
}
class DefaultPlugin final : public Plugin
{

  public:
    explicit DefaultPlugin(Corrade::PluginManager::AbstractManager &manager, const std::string &plugin)
        : Plugin{manager, plugin}
    {}

    void setup(ImGuiContext *imgui_ctx)
    {
        ImGui::SetCurrentContext(imgui_ctx);
        imnodes::Initialize();
    }
    void registerNodeFactories(IGraphManager &graph)
    {}
    void registerSlotFactories(IGraphManager &graph)
    {
        registerSlot<BoolSlot>(graph);
        registerSlot<FloatingSlot>(graph);
        registerSlot<IntSlot>(graph);
        registerSlot<StringSlotImpl>(graph);
        registerSlot<TriggerSlot>(graph);
    }
};
} // namespace dt::df::plugin

CORRADE_PLUGIN_REGISTER(DefaultPlugin, dt::df::plugin::DefaultPlugin, "de.mathisloge.dt.dataflow/1.0")
