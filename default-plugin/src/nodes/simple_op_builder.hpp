#pragma once
#define DT_DF_BUILD_SIMPLE_OP(OP_NAME)                                                                                 \
    class OP_NAME final : public SimpleOp                                                                              \
    {                                                                                                                  \
      public:                                                                                                          \
        static constexpr const char *kNodeKey = #OP_NAME;                                                              \
        static constexpr const char *kNodeName = #OP_NAME;                                                             \
        OP_NAME(IGraphManager &graph_manager);                                                                         \
        OP_NAME(IGraphManager &graph_manager, const nlohmann::json &);                                                 \
        ~##OP_NAME();                                                                                                  \
                                                                                                                       \
      private:                                                                                                         \
        double calc(const double a, const double b) const override;                                                    \
    };

#define DT_DF_IMPL_SIMPLE_OP_BEGIN(OP_NAME, TITLE, NAME_A, NAME_B, NAME_RES)                                           \
    OP_NAME::##OP_NAME(IGraphManager &graph_manager)                                                                   \
        : SimpleOp{graph_manager, kNodeKey, #TITLE, #NAME_A, #NAME_B, #NAME_RES}                                       \
    {}                                                                                                                 \
                                                                                                                       \
    OP_NAME::##OP_NAME(IGraphManager &graph_manager, const nlohmann::json &json)                                       \
        : SimpleOp{graph_manager, json}                                                                                \
    {}                                                                                                                 \
                                                                                                                       \
    OP_NAME::~##OP_NAME()                                                                                              \
    {}                                                                                                                 \
    double OP_NAME::calc(const double a, const double b) const                                                         \
    {

#define DT_DF_IMPL_SIMPLE_OP_END }
