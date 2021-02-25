#include "dt/df/core/window_node.hpp"
#include <imgui.h>
#include "dt/df/core/graph_manager.hpp"
#include "dt/df/core/number_slot.hpp"
namespace dt::df
{

static Slots createInputs(IGraphManager &graph_manager, Slots &&inputs);
class WindowNode::Impl final
{
    friend WindowNode;

  public:
    explicit Impl(const std::string &window_title)
        : window_title_{window_title}
        , window_is_visible_{false}
        , flags_{0}
    {}

    void initSlots(BaseNode &node)
    {
        node.inputByLocalId(0)->subscribe([this](auto slot) {
            auto nb_slot = dynamic_cast<const NumberSlot *>(slot);
            window_is_visible_ = static_cast<bool>(nb_slot->value());
        });
    }

  private:
    const std::string window_title_;
    bool window_is_visible_;
    ImGuiWindowFlags flags_;
};

WindowNode::WindowNode(IGraphManager &graph_manager,
                       const NodeKey &key,
                       const std::string &node_title,
                       const std::string &window_title,
                       Slots &&inputs,
                       Slots &&outputs)
    : BaseNode{graph_manager, key, node_title, createInputs(graph_manager, std::move(inputs)), std::move(outputs)}
    , impl_{new Impl{window_title}}
{
    impl_->initSlots(*this);
}
WindowNode::WindowNode(IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode{graph_manager, json}
{
    impl_->initSlots(*this);
}

void WindowNode::render()
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

void WindowNode::setWindowFlags(int window_flags)
{
    impl_->flags_ = window_flags;
}

int WindowNode::getWindowFlags() const
{
    return impl_->flags_;
}

WindowNode::~WindowNode()
{
    delete impl_;
}

Slots createInputs(IGraphManager &graph_manager, Slots &&inputs)
{
    Slots slots = inputs;

    try
    {
        const auto &slot_fac = graph_manager.getSlotFactory("BoolSlot");
        slots.emplace_back(
            slot_fac(graph_manager, SlotType::input, "show", 0, SlotFieldVisibility::without_connection));
    }
    catch (...)
    {}
    return slots;
}
} // namespace dt::df
