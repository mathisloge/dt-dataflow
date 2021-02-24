#pragma once
#include "dtdfcore_export.h"
#include <imgui.h>
#include <imnodes.h>
namespace dt::df::core
{
void DTDFCORE_EXPORT InitGui(ImGuiContext *imgui_ctx, imnodes::ImnodesContext *imnodes_ctx);
void DTDFCORE_EXPORT ShutdownGui();
} // namespace dt::df::core
