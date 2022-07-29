#pragma once

struct RenderParticles : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::child_update<Renderer, Renderer::Update>
	{
		.m_pName = "RenderParticles"
	};

	using query = std::tuple
		<
			xecs::query::must<ParticleTag>,
			xecs::query::none_of<Bullet, Zombie, PlayerTag>,
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

	__inline void operator()(const Position& pos, RenderDetails& renderDetails) const noexcept
	{
		glColor3f(
			renderDetails.mColour.r,
			renderDetails.mColour.g,
			renderDetails.mColour.b);

		glVertex2i(pos.x - renderDetails.mSize.x, pos.y - renderDetails.mSize.y);
		glVertex2i(pos.x - renderDetails.mSize.x, pos.y + renderDetails.mSize.y);
		glVertex2i(pos.x + renderDetails.mSize.x, pos.y + renderDetails.mSize.y);
		glVertex2i(pos.x + renderDetails.mSize.x, pos.y - renderDetails.mSize.y);
	}
};