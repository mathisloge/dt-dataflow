#include "dt/df/core/ui_node.hpp"
#include <imgui.h>
#include <imnodes.h>

namespace dt::df::core
{

class UiNode::Impl final
{
  public:
    explicit Impl(CoreNode &parent, const std::string &title)
        : parent_{parent}
        , title_{title}
        , position_was_updated_{false}
    {}
    void setPosition(int x, int y, bool is_screen_coords = false)
    {
        position_ = {static_cast<float>(x), static_cast<float>(y)};
        is_screen_coords_ = is_screen_coords;
        position_was_updated_ = true;
    }
    void updatePosIfNeeded()
    {
        if (position_was_updated_)
        {
            if (is_screen_coords_)
                imnodes::SetNodeEditorSpacePos(parent_.id(), position_);
            else
                imnodes::SetNodeScreenSpacePos(parent_.id(), position_);
            position_was_updated_ = false;
        }
    }

  public:
    CoreNode &parent_;
    const std::string title_;

  private:
    bool position_was_updated_;
    bool is_screen_coords_;
    ImVec2 position_;
};

UiNode::UiNode(CoreNode &parent, const std::string &title)
    : impl_{std::make_unique<Impl>(parent, title)}
{}

UiNode::~UiNode()
{}

const std::string &UiNode::title() const
{
    return impl_->title_;
}

void UiNode::render()
{
    impl_->updatePosIfNeeded();

    imnodes::BeginNode(impl_->parent_.id());
    imnodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(impl_->title_.c_str());
    imnodes::EndNodeTitleBar();

    for (auto &slot : impl_->parent_.inputs())
    {
        imnodes::BeginInputAttribute(slot.second->id());
        slot.second->render();
        imnodes::EndInputAttribute();
    }
    ImGui::PushID(this);
    renderCustomContent();
    ImGui::PopID();
    for (auto &slot : impl_->parent_.outputs())
    {
        imnodes::BeginOutputAttribute(slot.second->id());
        slot.second->render();
        imnodes::EndOutputAttribute();
    }
    imnodes::EndNode();
}

void UiNode::setPosition(int x, int y, bool is_screen_coords)
{
    impl_->setPosition(x, y, is_screen_coords);
}
void UiNode::renderCustomContent()
{}

} // namespace dt::df::core
