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

	__inline void OnGameStart() noexcept
	{
		auto& buttonArchetype = getOrCreateArchetype<ButtonArchetype>();

		buttonArchetype.CreateEntity(
			[&](Position& pos, Colour& colour, Scale& scale, Text& text, ButtonDetails& buttonDetails)
			{
				text.mActive = true;
				text.mValue = "START";
				
				text.mOffset.mValue = xcore::vector2{ -20, 2.75f };

				text.mFont = Text::Font::HELVETICA_12;
				text.mColour.mValue = xcore::vector3{ 0, 0, 0 };
				
				pos.x = Grid::MAX_RESOLUTION_WIDTH / 2;
				pos.y = Grid::MAX_RESOLUTION_HEIGHT / 2;
				
				colour.mValue = buttonDetails.mButtonColours[Button::State::DEFAULT];
				scale.mValue = xcore::vector2{ 30, 10 };
			});
	}

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