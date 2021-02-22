#pragma once
#include "dtdfeditor_export.h"
namespace dt::df::editor
{
    class DTDFEDITOR_EXPORT IdGenerator final
    {
    public:
        IdGenerator();
        int operator()();
        ~IdGenerator();

        IdGenerator(const IdGenerator &) = delete;
        IdGenerator &operator=(const IdGenerator &) = delete;

    private:
        void reset(int value = 0);

    private:
        class Impl;
        Impl *impl_;

        friend class GraphImpl;
    };
} // namespace dt::df