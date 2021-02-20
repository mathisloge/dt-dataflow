#pragma once
#include "dtdfeditor_export.h"
#include <imgui.h>

namespace dt::df::editor
{
    void DTDFEDITOR_EXPORT InitGui(ImGuiContext *imgui_ctx);
    void DTDFEDITOR_EXPORT ShutdownGui();
}
