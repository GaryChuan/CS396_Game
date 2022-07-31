#pragma once

struct RenderPlayer : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::child_update<Renderer, Renderer::Update>
	{
		.m_pName = "RenderPlayer"
	};

	using query = std::tuple
		<
		xecs::query::must<PlayerTag>,
		xecs::query::none_of<Bullet, Zombie, ParticleTag>,
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

	__inline void operator()(const Position& pos, const Weapon& weapon, RenderDetails& renderDetails) const noexcept
	{
		glColor3f(
			renderDetails.mColour.r,
			renderDetails.mColour.g,
			renderDetails.mColour.b);

		glVertex2i(pos.x - renderDetails.mSize.x, pos.y - renderDetails.mSize.y);
		glVertex2i(pos.x - renderDetails.mSize.x, pos.y + renderDetails.mSize.y);
		glVertex2i(pos.x + renderDetails.mSize.x, pos.y + renderDetails.mSize.y);
		glVertex2i(pos.x + renderDetails.mSize.x, pos.y - renderDetails.mSize.y);

		constexpr float ammoOffset{ 7.5f };
		constexpr xcore::vector2 ammoSize{ 1.f, 1.f };

		// Render ammo count
		for (int i = 0; i < weapon.GetAmmoCount(); ++i)
		{
			glColor3f(0, 1, 1);

			const auto xOffset = -10.f + i * 2.5f;

			glVertex2i(pos.x + xOffset - ammoSize.m_X, pos.y + ammoOffset - ammoSize.m_Y);
			glVertex2i(pos.x + xOffset - ammoSize.m_X, pos.y + ammoOffset + ammoSize.m_Y);
			glVertex2i(pos.x + xOffset + ammoSize.m_X, pos.y + ammoOffset + ammoSize.m_Y);
			glVertex2i(pos.x + xOffset + ammoSize.m_X, pos.y + ammoOffset - ammoSize.m_Y);
		}
	}
};