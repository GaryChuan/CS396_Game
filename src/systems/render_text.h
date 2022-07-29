#pragma once

struct RenderText : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::child_update<Renderer, Renderer::Update>
	{
		.m_pName = "RenderText"
	};

	using query = std::tuple
		<
			xecs::query::must<Text>
		>;

	void OnPreUpdate() noexcept
	{
	}

	void OnPostUpdate() noexcept
	{
	}

	__inline void operator()(const Position& position, Text& text) const noexcept
	{
		if (!text.mActive || text.mValue.empty())
		{
			return;
		}

		glColor3f(1.f, 1.f, 1.f);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 1024, 0, 800);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRasterPos2i(position.x + text.mOffset.x, 800 - (position.y + text.mOffset.y));

		for (int i = 0; i < text.mValue.length(); ++i)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text.mValue[i]);
		}

		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
};