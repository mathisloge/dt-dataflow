#include "dt/df/core/window_base_node.hpp"
#include <variant>
#include <imgui.h>
#include "dt/df/core/base_slot.hpp"
namespace dt::df::core
{

class WindowBaseNode::Impl final
{
    friend WindowBaseNode;

  public:
    explicit Impl(const std::string &window_title)
        : window_title_{window_title}
        , window_is_visible_{false}
        , flags_{0}
    {}

  private:
    const std::string window_title_;
    bool window_is_visible_;
    ImGuiWindowFlags flags_;
};

WindowBaseNode::WindowBaseNode(IGraphManager &graph_manager,
                               const NodeKey &key,
                               const std::string &node_title,
                               const std::string &window_title)
    : BaseNode{graph_manager, key, node_title}
    , impl_{std::make_unique<Impl>(window_title)}
{}
void WindowBaseNode::init(core::IGraphManager &graph_manager)
{
    std::dynamic_pointer_cast<BaseSlot<const std::variant<bool, int, float, double> &>>(
        addInput(graph_manager, "NumberSlot", "isVisible", 0))
        ->connectToNodeFnc([this](const auto &number) {
            impl_->window_is_visible_ = std::visit([](auto ta) { return static_cast<bool>(ta); }, number);
        });
}
void WindowBaseNode::evaluate()
{}

void WindowBaseNode::render()
{
    BaseNode::render();
    if (impl_->window_is_visible_)
    {
        if (ImGui::Begin(impl_->window_title_.c_str(), &impl_->window_is_visible_, impl_->flags_))
        {
            drawWindow();
            ImGui::End();
        }
    }
}

void WindowBaseNode::setWindowFlags(int window_flags)
{
    impl_->flags_ = window_flags;
}

int WindowBaseNode::getWindowFlags() const
{
    return impl_->flags_;
}

WindowBaseNode::~WindowBaseNode()
{}
} // namespace dt::df::core
