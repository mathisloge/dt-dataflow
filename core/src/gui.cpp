#include "dt/df/core/gui.hpp"
#include <imgui.h>
#include <imnodes.h>
namespace dt::df::core
{
void InitGui(ImGuiContext *imgui_ctx, imnodes::Context *imnodes_ctx)
{
#ifndef DTDFCORE_STATIC_DEFINE
#ifdef WIN32
    ImGui::SetCurrentContext(imgui_ctx);
    imnodes::SetCurrentContext(imnodes_ctx);
#endif
#endif
}

void ShutdownGui()
{
#ifndef DTDFCORE_STATIC_DEFINE
#ifdef WIN32
    ImGui::SetCurrentContext(nullptr);
#endif
#endif
}
} // namespace dt::df::core
