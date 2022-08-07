/******************************************************************************
filename: render_player.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of RenderPlayer which manages the rendering
  of all player.
******************************************************************************/
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

	__inline void operator()(const Position& pos, const Weapon& weapon, const Health& health, Colour& colour, Scale& scale) const noexcept
	{
		glColor3f(colour.r, colour.g, colour.b);

		glVertex2i(pos.x - scale.x, pos.y - scale.y);
		glVertex2i(pos.x - scale.x, pos.y + scale.y);
		glVertex2i(pos.x + scale.x, pos.y + scale.y);
		glVertex2i(pos.x + scale.x, pos.y - scale.y);

		constexpr float barScale = 20.f;
		constexpr float xOffset = barScale / 2.f;
		constexpr float yOffset = 10.5f;
		constexpr float ammoYOffset{ 15.f };
		const auto xPivot = pos.x - xOffset;

		// Render ammo count
		const auto ammoCount = static_cast<float>(weapon.GetAmmoCount());

		if (ammoCount > 0)
		{
			const auto currentWeaponScale = ammoCount / weapon.GetMaxAmmoCount() * barScale;

			glColor3f(0, 1, 1);

			glVertex2i(xPivot, pos.y + ammoYOffset - 1.f);
			glVertex2i(xPivot, pos.y + ammoYOffset + 1.f);
			glVertex2i(xPivot + currentWeaponScale, pos.y + ammoYOffset + 1.f);
			glVertex2i(xPivot + currentWeaponScale, pos.y + ammoYOffset - 1.f);
		}

		if (health.mValue > 0)
		{
			// Render health
			const auto currentHealthScale = health.mValue / PLAYER_MAX_HEALTH * barScale;

			glColor3f(1, 0, 0);

			glVertex2i(xPivot, pos.y + yOffset - 1.f);
			glVertex2i(xPivot, pos.y + yOffset + 1.f);
			glVertex2i(xPivot + currentHealthScale, pos.y + yOffset + 1.f);
			glVertex2i(xPivot + currentHealthScale, pos.y + yOffset - 1.f);
		}
	}
};