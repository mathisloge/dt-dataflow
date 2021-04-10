#pragma once
#include "base_slot.hpp"
#include "dtdfcore_export.h"
namespace dt::df
{

class DTDFCORE_EXPORT CalculateSlot : public BaseSlot
{
  public:
    static constexpr std::string_view kKey = "CalculateSlot";
    using BaseSlot::BaseSlot;

    void accept(const BaseSlot *slot) override;
    bool canConnect(const BaseSlot *const slot) const override;
};

} // namespace dt::df
