/******************************************************************************
filename: particle_tag.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of the ParticleTag tag component.
******************************************************************************/
#pragma once

struct ParticleTag
{
    constexpr static auto typedef_v = xecs::component::type::tag
    {
        .m_pName = "ParticleTag"
    };
};