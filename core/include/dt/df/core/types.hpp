#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>
namespace dt::df
{
namespace core
{
class IGraphManager;
class BaseNode;
class CoreSlot;
} // namespace core

using NodeId = int;
using NodeKey = std::string;
using NodePtr = std::shared_ptr<core::BaseNode>;
using SlotPtr = std::shared_ptr<core::CoreSlot>;
using SlotId = int;
using SlotMap = std::unordered_map<SlotId /*local_id*/, SlotPtr>;
using SlotName = std::string;
using SlotKey = std::string_view;
enum class SlotType
{
    input,
    output
};

enum class SlotFieldVisibility
{
    never,
    without_connection,
    always
};

using EdgeId = int;
using NodePtr = std::shared_ptr<core::BaseNode>;
using NodeFactory = std::function<NodePtr(core::IGraphManager &)>;
using NodeDeserializationFactory = std::function<NodePtr(core::IGraphManager &, const nlohmann::json &)>;

using SlotFactory = std::function<SlotPtr(core::IGraphManager &, SlotType, const SlotName &, SlotId, SlotFieldVisibility)>;
using SlotDeserializationFactory = std::function<SlotPtr(const nlohmann::json &)>;

} // namespace dt::df
