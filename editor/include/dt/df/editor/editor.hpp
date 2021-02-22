#pragma once
#include "data_flow_graph.hpp"
#include "dtdfeditor_export.h"

namespace dt::df::editor
{
class DTDFEDITOR_EXPORT Editor
{
  public:
    static constexpr std::string_view kDndTarget = "DND_DATAFLOW";

  public:
    Editor();
    Editor(const Editor &) = delete;
    Editor &operator=(const Editor &) = delete;

    void render();
    void renderNodeDisplayTree(const NodeDisplayDrawFnc &draw_fnc) const;
    DataFlowGraph &graph();
    const DataFlowGraph &graph() const;

    virtual ~Editor();

  private:
    class Impl;
    Impl *impl_;
};
} // namespace dt::df::editor
