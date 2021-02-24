#include "simple_cmps.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace dt::df::cmp
{
DT_DF_IMPL_SIMPLE_CMP_BEGIN(Less, less, a, b, result)
return a < b;
DT_DF_IMPL_SIMPLE_CMP_END

DT_DF_IMPL_SIMPLE_CMP_BEGIN(LEQ, leq, a, b, result)
return a <= b;
DT_DF_IMPL_SIMPLE_CMP_END

DT_DF_IMPL_SIMPLE_CMP_BEGIN(EQ, eq, a, b, result)
return std::abs(a - b) < std::numeric_limits<double>::epsilon();
DT_DF_IMPL_SIMPLE_CMP_END

DT_DF_IMPL_SIMPLE_CMP_BEGIN(NEQ, neq, a, b, result)
return std::abs(a - b) > std::numeric_limits<double>::epsilon();
DT_DF_IMPL_SIMPLE_CMP_END

DT_DF_IMPL_SIMPLE_CMP_BEGIN(GEQ, geq, a, b, result)
return a >= b;
DT_DF_IMPL_SIMPLE_CMP_END

DT_DF_IMPL_SIMPLE_CMP_BEGIN(Greater, greater, a, b, result)
return a > b;
DT_DF_IMPL_SIMPLE_CMP_END
} // namespace dt::df::operators
