#pragma once

struct PlayerLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
		{
			.m_pName = "PlayerLogic"
		};

	PlayerLogic(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance { gameMgr }
	{
	}


	using query = std::tuple
		<
			xecs::query::must<PlayerTag>,
			xecs::query::none_of<Bullet>
		>;

	void OnGameStart() noexcept
	{
		// Create player
		mPlayerArchetype = &getOrCreateArchetype<PlayerArchetype>();

		mPlayerArchetype->CreateEntity(
			[&](
				Position& pos, 
				Velocity& vel, 
				Health& health, 
				Weapon& weapon,
				RenderDetails& renderDetails,
				Text& text, 
				GridCell& gridCell)
			{
				pos.mValue = xcore::vector2
				{ 
					Grid::MAX_RESOLUTION_WIDTH * 0.5f, 
					Grid::MAX_RESOLUTION_HEIGHT * 0.5f
				};
				vel.mValue = xcore::vector2{ 0, 0 };

				health.mValue = 100;

				renderDetails.mColour = Colour{ 1, 1, 1 };
				renderDetails.mSize = Size{ 3 , 3 };

				weapon.mCurrentWeapon = Weapon::Type::PISTOL;

				text.mValue			= Weapon::names.front();
				text.mActive		= false;
				text.mOffset.mValue = xcore::vector2{ -15 , -10 };

				gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);
			});
	}

	__inline void operator()(Weapon& weapon, Text& text, const Health& health)
	{
		switch(weapon.mState)
		{
		case Weapon::State::RELOAD:
			weapon.mState = Weapon::State::RELOADING;
			weapon.mReloadTimer = 0.f;
			text.mValue = "Reloading";
			text.mActive = true;
			[[fallthrough]];
		case Weapon::State::RELOADING:
			
			weapon.mReloadTimer += 1 / 60.f;

			if (weapon.mReloadTimer >= weapon.GetReloadRate())
			{
				weapon.mState = Weapon::State::INACTIVE;
				weapon.Reloaded();
				text.mValue = Weapon::names[static_cast<int>(weapon.mCurrentWeapon)];
			}
			break;

		case Weapon::State::FIRING:
			break;

		case Weapon::State::INACTIVE:
			break;
		}
	}

private:
	xecs::archetype::instance* mPlayerArchetype{};
};