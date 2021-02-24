#pragma once
#define DT_DF_BUILD_SIMPLE_CMP(OP_NAME)                                                                                \
    class OP_NAME final : public SimpleCmp                                                                             \
    {                                                                                                                  \
      public:                                                                                                          \
        static constexpr const char *kNodeKey = #OP_NAME;                                                              \
        static constexpr const char *kNodeName = #OP_NAME;                                                             \
        OP_NAME(IGraphManager &graph_manager);                                                                         \
        OP_NAME(IGraphManager &graph_manager, const nlohmann::json &);                                                 \
        ~##OP_NAME();                                                                                                  \
                                                                                                                       \
      private:                                                                                                         \
        bool cmp(const double a, const double b) const override;                                                       \
    };

#define DT_DF_IMPL_SIMPLE_CMP_BEGIN(OP_NAME, TITLE, NAME_A, NAME_B, NAME_RES)                                          \
    OP_NAME::##OP_NAME(IGraphManager &graph_manager)                                                                   \
        : SimpleCmp{graph_manager, kNodeKey, #TITLE, #NAME_A, #NAME_B, #NAME_RES}                                      \
    {}                                                                                                                 \
                                                                                                                       \
    OP_NAME::##OP_NAME(IGraphManager &graph_manager, const nlohmann::json &json)                                       \
        : SimpleCmp{graph_manager, json}                                                                               \
    {}                                                                                                                 \
                                                                                                                       \
    OP_NAME::~##OP_NAME()                                                                                              \
    {}                                                                                                                 \
    bool OP_NAME::cmp(const double a, const double b) const                                                            \
    {
#define DT_DF_IMPL_SIMPLE_CMP_END }
