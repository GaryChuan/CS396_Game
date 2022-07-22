#pragma once
struct PlayerTag
{
    constexpr static auto typedef_v = xecs::component::type::tag
    {
        .m_pName = "PlayerTag"
    };
};