#pragma once

struct Renderer : xecs::system::instance
{
	constexpr static auto typedef_v = xecs::system::type::update
	{
		.m_pName = "Renderer"
	};

	using Update = xecs::event::instance<>;

	using events = std::tuple<Update>;

	__inline void OnUpdate() noexcept
	{
        //
        // Begin of the rendering
        //
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        glViewport(0, 0, 1024, 800);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 1024, 0, 800, -1, 1);
        glScalef(1, -1, 1);
        glTranslatef(0, -800, 0);

        //
        // Let all the system that depends on me
        //
        SendEventFrom<Update>(this);

        //
        // Page Flip
        //
        glutSwapBuffers();
	}

    __inline void OnGameEnd() noexcept
    {
        // Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
    }
};