#pragma once

struct RenderButtons : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::child_update<Renderer, Renderer::Update>
		{
			.m_pName = "RenderButtons"
		};

	using query = std::tuple
		<
			xecs::query::must<Button, ButtonDetails>
		>;

	void OnPreUpdate() noexcept
	{
		glBegin(GL_QUADS);
	}

	void OnPostUpdate() noexcept
	{
		glEnd();
	}

	__inline void operator()(
		const Position& pos, 
		const Scale& scale,
		Colour& colour) const noexcept
	{
		glColor3f(colour.r, colour.g, colour.b);

		glVertex2i(pos.x - scale.x, pos.y - scale.y);
		glVertex2i(pos.x - scale.x, pos.y + scale.y);
		glVertex2i(pos.x + scale.x, pos.y + scale.y);
		glVertex2i(pos.x + scale.x, pos.y - scale.y);
	}
};