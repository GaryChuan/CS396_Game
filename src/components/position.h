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