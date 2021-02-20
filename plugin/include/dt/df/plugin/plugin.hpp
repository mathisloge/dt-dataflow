#pragma once
namespace dt::df::plugin
{
    class Plugin
    {
    public:
        Plugin();
        Plugin(const Plugin &) = delete;
        Plugin &operator=(const Plugin &) = delete;

        virtual ~Plugin();
    };
} // namespace dt::df::plugin
