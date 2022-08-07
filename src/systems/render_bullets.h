/******************************************************************************
filename: render_bullets.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of RenderButton which renders all
  bullets.
******************************************************************************/
#pragma once

struct RenderBullets : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::child_update<Renderer, Renderer::Update>
		{
			.m_pName = "RenderBullets"
		};

	using query = std::tuple
		<
			xecs::query::must<Bullet>,
			xecs::query::one_of<entity>
		>;

	void OnPreUpdate() noexcept
	{
	}

	void OnPostUpdate() noexcept
	{
	}

	__inline void operator()(const Position& pos) const noexcept
	{
		constexpr auto M_PI = 3.14159265358979323846f;
		constexpr auto radius = 2;

		glColor3f(1, 1, 1);

		glBegin(GL_TRIANGLE_FAN);
		for (float i = 0.0f; i <= 360; i++)
		{
			float angleRad = M_PI * i / 180;

			glVertex2f(
				radius * cos(angleRad) + pos.x,
				radius * sin(angleRad) + pos.y);
		}
		glEnd();
	}

};