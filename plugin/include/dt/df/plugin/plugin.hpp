#pragma once
#include <Corrade/PluginManager/AbstractPlugin.h>
#include <Magnum/GL/Context.h>
#include <dt/df/core/graph_manager.hpp>
#include <imgui.h>
#include <imnodes.h>
namespace dt::df::plugin
{
class Plugin : public Corrade::PluginManager::AbstractPlugin
{
  public:
    explicit Plugin(Corrade::PluginManager::AbstractManager &manager, const std::string &plugin)
        : AbstractPlugin{manager, plugin}
    {}
    Plugin(const Plugin &) = delete;
    Plugin &operator=(const Plugin &) = delete;

    //! \attention call ImGui::SetCurrentContext(imgui_ctx); and imnodes::Initialize();
    virtual void setup(Magnum::GL::Context &gl_ctx, ImGuiContext *imgui_ctx, imnodes::Context *imnodes_ctx) = 0;
    virtual void registerNodeFactories(IGraphManager &graph) = 0;
    virtual void registerSlotFactories(IGraphManager &graph) = 0;

    static std::string pluginInterface()
    {
        return "de.mathisloge.dt.dataflow/1.0";
    }

    static std::vector<std::string> pluginSearchPaths()
    {
        return {"C:/dev/install/device_tester/bin/dataflow/dbg"};
    }

    virtual ~Plugin() = default;
};
} // namespace dt::df::plugin
