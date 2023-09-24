#include "IcyTowerContext.hpp"

IcyTowerContext::IcyTowerContext(OS::Process process) :
        _process{std::move(process)},
        _floor_level{_process, 0x4ccbb4},
        _gravity{_process, 0x4AD810}
{}

OS::Symbol<uint32_t> &IcyTowerContext::getFloorLevel()
{
    return _floor_level;
}

OS::Symbol<double> &IcyTowerContext::getGravity()
{
    return _gravity;
}
