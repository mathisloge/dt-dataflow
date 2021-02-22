#include "dt/df/core/base_slot.hpp"
namespace dt::df
{
    class BaseSlot::Impl final
    {
    public:
        explicit Impl(const SlotKey &key,
                      const SlotId id,
                      const SlotType type,
                      const SlotName &name,
                      const SlotId local_id,
                      SlotFieldVisibility visibility_rule)
            : key_{key}, id_{id}, type_{type}, name_{name}, local_id_{local_id}, visibility_rule_{visibility_rule}, connection_counter_(0)
        {
        }

        void to_json(nlohmann::json &j) const
        {
            j = nlohmann::json{
                {"key", key_},
                {"id", id_},
                {"localid", local_id_},
                {"name", name_},
                {"type", type_},
                {"visibility", visibility_rule_}};
        }

        ~Impl()
        {
        }

    private:
        const SlotKey key_;
        const SlotId id_;
        const SlotType type_;
        const SlotName name_;

        SlotId local_id_;
        SlotFieldVisibility visibility_rule_;
        ValueChangedSignal value_changed_sig_;
        EvaluationSignal evaluation_changed_sig_;
        std::atomic_int connection_counter_;
        friend BaseSlot;
    };

    BaseSlot::BaseSlot(const SlotKey &key,
                       const SlotId id,
                       const SlotType type,
                       const SlotName &name,
                       const SlotId local_id,
                       SlotFieldVisibility visibility_rule)
        : impl_{new BaseSlot::Impl{key, id, type, name, local_id, visibility_rule}}
    {
    }

    BaseSlot::BaseSlot(const nlohmann::json &json)
    {
        impl_ = new BaseSlot::Impl{json["key"], json["id"], json["type"], json["name"], json["localid"], json["visibility"]};
    }

    const SlotKey &BaseSlot::key() const
    {
        return impl_->key_;
    }
    SlotId BaseSlot::id() const
    {
        return impl_->id_;
    }
    SlotId BaseSlot::localId() const
    {
        return impl_->local_id_;
    }
    void BaseSlot::localId(const SlotId id)
    {
        impl_->local_id_ = id;
    }

    SlotType BaseSlot::type() const
    {
        return impl_->type_;
    }

    const SlotName &BaseSlot::name() const
    {
        return impl_->name_;
    }

    boost::signals2::connection BaseSlot::subscribe(const ValueChangedSignal::slot_type &sub)
    {
        return impl_->value_changed_sig_.connect(sub);
    }

    void BaseSlot::valueChanged()
    {
        impl_->value_changed_sig_(this);
    }

    bool BaseSlot::hasConnection() const
    {
        return impl_->connection_counter_ > 0;
    }

    void BaseSlot::render()
    {
    }

    SlotFieldVisibility BaseSlot::visibility_rule() const
    {
        return impl_->visibility_rule_;
    }
    void BaseSlot::visibility_rule(SlotFieldVisibility visibility_rule)
    {
        impl_->visibility_rule_ = visibility_rule;
    }

    bool BaseSlot::showField() const
    {
        return impl_->visibility_rule_ != SlotFieldVisibility::never && (impl_->visibility_rule_ == SlotFieldVisibility::always ||
                                                                         !(hasConnection() && impl_->visibility_rule_ == SlotFieldVisibility::without_connection));
    }

    boost::signals2::connection BaseSlot::connectEvaluation(const EvaluationSignal::slot_type &sub)
    {
        return impl_->evaluation_changed_sig_.connect(sub);
    }

    void BaseSlot::needsReevaluation()
    {
        impl_->evaluation_changed_sig_(impl_->id_);
    }

    void BaseSlot::connectEvent()
    {
        impl_->connection_counter_++;
    }
    void BaseSlot::disconnectEvent()
    {
        impl_->connection_counter_--;
    }

    void BaseSlot::to_json(nlohmann::json &j) const
    {
        impl_->to_json(j);
    }

    BaseSlot::~BaseSlot()
    {
        delete impl_;
    }

} // namespace dt::df