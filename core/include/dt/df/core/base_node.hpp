#pragma once
#include <nlohmann/json.hpp>
#include "dtdfcore_export.h"
#include "types.hpp"

namespace dt::df
{
class DTDFCORE_EXPORT BaseNode
{
  public:
    BaseNode(
        IGraphManager &graph_manager, const NodeKey &key, const std::string &title, Slots &&inputs, Slots &&outputs);
    BaseNode(IGraphManager &graph_manager, const nlohmann::json &);
    BaseNode(const BaseNode &) = delete;
    BaseNode &operator=(const BaseNode &) = delete;
    virtual ~BaseNode();

    NodeId id() const;
    const NodeKey &key() const;
    virtual void render();
    void setPosition(int x, int y, bool is_screen_coords = false);
    
    virtual void calculate() = 0;

    const Slots &inputs() const;
    const Slots &outputs() const;
    SlotPtr inputs(const SlotId id) const;
    SlotPtr outputs(const SlotId id) const;
    SlotPtr inputByLocalId(const SlotId id) const;
    SlotPtr outputByLocalId(const SlotId id) const;

    virtual void to_json(nlohmann::json &j) const;

  protected:
    virtual void renderCustomContent();
    void calculateIfNoFlow();
    void triggerFlow();

  private:
    class Impl;
    Impl *impl_;
};
} // namespace dt::df
