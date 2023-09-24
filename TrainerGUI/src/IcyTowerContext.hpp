#pragma once


#include "process.hpp"
#include "symbol.hpp"

class IcyTowerContext
{
public:
    explicit IcyTowerContext(OS::Process process);
    [[nodiscard]] OS::Symbol<uint32_t> &getFloorLevel();
    [[nodiscard]] OS::Symbol<double> &getGravity();

private:
    OS::Process _process;
    OS::Symbol<uint32_t> _floor_level;
    OS::Symbol<double> _gravity;
};
