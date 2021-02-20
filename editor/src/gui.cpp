#include "dt/df/editor/gui.hpp"
#include <imgui.h>
#include <imnodes.h>
namespace dt::df::editor
{
    void InitGui(ImGuiContext *imgui_ctx)
    {
#ifndef DTDFEDITOR_STATIC_DEFINE
#ifdef WIN32
        ImGui::SetCurrentContext(imgui_ctx);
        imnodes::Initialize();
#endif
#endif
    }

    void ShutdownGui()
    {
#ifndef DTDFEDITOR_STATIC_DEFINE
#ifdef WIN32
        imnodes::Shutdown();
        ImGui::SetCurrentContext(nullptr);
#endif
#endif
    }
} // namespace dt::df::editor
