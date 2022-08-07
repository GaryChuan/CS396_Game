/******************************************************************************
filename: player_logic.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of PlayerLogic which manages the player
  logic. Specifically the state of the weapon such as if it is shooting
  or reloading etc..
******************************************************************************/
#pragma once

struct PlayerLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
		{
			.m_pName = "PlayerLogic"
		};

	// Hacky way of doing next scene
	__inline static GameStateManager* mGSMPtr = nullptr;

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
				Colour& colour,
				Scale& scale,
				Text& text, 
				GridCell& gridCell)
			{
				pos.mValue = xcore::vector2
				{ 
					Grid::MAX_RESOLUTION_WIDTH * 0.5f, 
					Grid::MAX_RESOLUTION_HEIGHT * 0.5f
				};
				vel.mValue = xcore::vector2{ 0, 0 };

				health.mValue = PLAYER_MAX_HEALTH;

				colour.mValue = xcore::vector3{ 1, 1, 1 };
				scale.mValue = xcore::vector2{ 3 , 3 };

				weapon.mCurrentWeapon = Weapon::Type::PISTOL;

				text.mValue			= Weapon::names.front();
				text.mActive		= false;
				text.mOffset.mValue = xcore::vector2{ -21.5 , -10 };

				gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);
			});
	}

	__inline void operator()(Weapon& weapon, Text& text, const Health& health)
	{
		assert(mGSMPtr);

		if (health.mValue <= 0)
		{
			mGSMPtr->SetNextScene(SceneState::RETRY_MENU);
			return;
		}

		switch(weapon.mState)
		{
		case Weapon::State::RELOAD:
			weapon.mState = Weapon::State::RELOADING;
			weapon.mReloadTimer = 0.f;
			weapon.mShootTimer = 0.f;
			weapon.mCanShoot = true;
			text.mValue = "Reloading";
			text.mActive = true;
			[[fallthrough]];

		case Weapon::State::RELOADING:
			weapon.mReloadTimer += F_DT;

			text.mValue = "Reloading";

			for (int i = 0; i < (int)weapon.mReloadTimer + 1; ++i)
			{
				text.mValue += ".";
			}

			if (weapon.mReloadTimer >= weapon.GetReloadRate())
			{
				weapon.mState = Weapon::State::INACTIVE;
				weapon.Reloaded();
				text.mActive = false;
				text.mValue = Weapon::names[static_cast<int>(weapon.mCurrentWeapon)];
			}
			break;

		case Weapon::State::FIRING:

			if (weapon.mCanShoot == false)
			{
				weapon.mShootTimer += F_DT;

				if (weapon.mShootTimer >= weapon.GetFireRate())
				{
					weapon.mShootTimer = 0.f;
					weapon.mCanShoot = true;
				}
			}
			break;

		case Weapon::State::INACTIVE:
			weapon.mCanShoot = true;
			break;
		}
	}

	void OnGameEnd() noexcept
	{
		mGSMPtr = nullptr;
	}

private:
	xecs::archetype::instance* mPlayerArchetype{};
};