#pragma once
#include "dtdfcore_export.h"
#include <imgui.h>

namespace dt::df::core
{
    void DTDFCORE_EXPORT InitGui(ImGuiContext *imgui_ctx);
    void DTDFCORE_EXPORT ShutdownGui();
}