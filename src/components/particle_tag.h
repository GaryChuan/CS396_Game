#pragma once

struct ParticleTag
{
    constexpr static auto typedef_v = xecs::component::type::tag
    {
        .m_pName = "ParticleTag"
    };
};