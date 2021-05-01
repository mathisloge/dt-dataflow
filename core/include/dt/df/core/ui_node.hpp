#pragma once
#include <memory>
#include <string>
#include "core_node.hpp"
#include "dtdfcore_export.h"

namespace dt::df::core
{
class DTDFCORE_EXPORT UiNode
{
  public:
    explicit UiNode(CoreNode &parent, const std::string &title);
    UiNode(const UiNode &) = delete;
    UiNode &operator=(const UiNode &) = delete;
    virtual ~UiNode();

    const std::string &title() const;

    /**
     * @brief only called if the graph is visibile
     * use @see renderCustomContent() to render some custom content into the node
     */
    virtual void render();
    void setPosition(int x, int y, bool is_screen_coords);

    virtual void renderCustomContent();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace dt::df::core
