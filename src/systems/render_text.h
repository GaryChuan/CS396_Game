/******************************************************************************
filename: render_text.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of RenderText which manages the rendering
  of all text.
******************************************************************************/
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

		glColor3f(text.mColour.r, text.mColour.g, text.mColour.b);

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
			switch (text.mFont)
			{
			case Text::Font::HELVETICA_10:
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text.mValue[i]);
				break;
			case Text::Font::HELVETICA_12:
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text.mValue[i]);
				break;
			case Text::Font::HELVETICA_18:
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text.mValue[i]);
				break;
			}
		}

		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
};