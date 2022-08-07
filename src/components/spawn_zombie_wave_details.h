/******************************************************************************
filename: spawn_zombie_wave_details.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of SpawnZombieWaveDetails component.
  It is used for determing what is the ID of the next zombie wave to spawn.
******************************************************************************/
#pragma once

struct SpawnZombieWaveDetails
{
    constexpr static auto typedef_v = xecs::component::type::data
    {
        .m_pName = "SpawnZombieWaveDetails"
    };

    int mID;
};