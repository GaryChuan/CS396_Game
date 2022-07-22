#pragma once

struct Input : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::update
    {
        .m_pName = "Input"
    };

    using Keys = std::array<char, 0xff + 1>;

    using Update = xecs::event::instance<const Keys&>;

    using events = std::tuple<Update>;

    __inline void OnUpdate() noexcept
    {
        // Collect input from Glut

        // .. SendEventFrom<Update>(this, mKeys);
    }

private:
    // Keys mKeys{};
};