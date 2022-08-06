#pragma once

struct SpawnZombieWaveDetails
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "SpawnZombieWaveDetails"
    };

    int mID;
};