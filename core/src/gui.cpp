#include "dt/df/core/gui.hpp"
#include <imgui.h>
#include <imnodes.h>
namespace dt::df::core
{
    void InitGui(ImGuiContext *imgui_ctx)
    {
#ifndef DTDFCORE_STATIC_DEFINE
#ifdef WIN32
        ImGui::SetCurrentContext(imgui_ctx);
        imnodes::Initialize();
#endif
#endif
    }

    void ShutdownGui()
    {
#ifndef DTDFCORE_STATIC_DEFINE
#ifdef WIN32
        imnodes::Shutdown();
        ImGui::SetCurrentContext(nullptr);
#endif
#endif
    }
} // namespace dt::df::core
