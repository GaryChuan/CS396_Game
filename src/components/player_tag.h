/******************************************************************************
filename: player_tag.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of the PlayerTag tag component.
******************************************************************************/
#pragma once

struct PlayerTag
{
    constexpr static auto typedef_v = xecs::component::type::tag
    {
        .m_pName = "PlayerTag"
    };
};