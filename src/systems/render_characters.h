#pragma once

struct RenderCharacters : xecs::system::instance
{
	constexpr static auto typedef_v 
		= xecs::system::type::child_update<Renderer, Renderer::Update>
		{
			.m_pName = "RenderCharacters"
		};
	
	using query = std::tuple
		<
			xecs::query::none_of<Bullet>,
			xecs::query::one_of<entity>
		>;

	void OnPreUpdate() noexcept
	{
		glBegin(GL_QUADS);
	}

	void OnPostUpdate() noexcept
	{
		glEnd();
	}

	__inline void operator()(const Position& pos) const noexcept
	{
		constexpr auto size = 3;

		glVertex2i(pos.x - size, pos.y - size);
		glVertex2i(pos.x - size, pos.y + size);
		glVertex2i(pos.x + size, pos.y + size);
		glVertex2i(pos.x + size, pos.y - size);
	}
};