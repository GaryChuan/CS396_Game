/******************************************************************************
filename: render_zombies.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of RenderZombies which manages the rendering
  of all zombies.
******************************************************************************/
#pragma once

struct RenderZombies : xecs::system::instance
{
	constexpr static auto typedef_v 
		= xecs::system::type::child_update<Renderer, Renderer::Update>
		{
			.m_pName = "RenderZombies"
		};
	
	using query = std::tuple
		<
			xecs::query::must<Zombie>,
			xecs::query::none_of<Bullet, ParticleTag, PlayerTag>,
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

	__inline void operator()(const Position& pos, Colour& colour, Scale& scale) const noexcept
	{
		glColor3f(colour.r, colour.g, colour.b);

		glVertex2i(pos.x - scale.x, pos.y - scale.y);
		glVertex2i(pos.x - scale.x, pos.y + scale.y);
		glVertex2i(pos.x + scale.x, pos.y + scale.y);
		glVertex2i(pos.x + scale.x, pos.y - scale.y);
	}
};