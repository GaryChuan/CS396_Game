/******************************************************************************
filename: position.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of Position component.
******************************************************************************/
struct Position
{
    constexpr static auto typedef_v 
        = xecs::component::type::data
        {
            .m_pName = "Position"
        };

    union
    {
        struct
        {
            float x;
            float y;
        };

        xcore::vector2 mValue{};
    };
};