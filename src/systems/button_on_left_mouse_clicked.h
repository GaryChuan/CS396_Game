#pragma once

struct ButtonOnLeftMouseClicked : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnMouseLeftClicked>
	{
		.m_pName = "ButtonOnLeftMouseClicked"
	};

	ButtonOnLeftMouseClicked(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		mQueryButtons.m_Must.AddFromComponents<Button>();
	}

	void OnEvent(int mouseX, int mouseY)
	{
		Foreach(
			Search(mQueryButtons),
			[&]
		(
			const Position& pos,
			const Scale& scale,
			Colour& colour,
			Button& button
			)
			{
				const auto topLeft = pos.mValue - scale.mValue;
				const auto btmRight = pos.mValue + scale.mValue;

				if (topLeft.m_X <= mouseX && mouseX <= btmRight.m_X
				&& topLeft.m_Y <= mouseY && mouseY <= btmRight.m_Y)
				{
					button.mState = Button::State::PRESSED;
					return true;
				}

				return false;
			}
		);
	}

private:
	xecs::query::instance mQueryButtons{};
};