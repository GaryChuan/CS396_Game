/******************************************************************************
filename: player_input_on_mouse_left_held.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of PlayerInputOnMouseLeftHeld which handles
  shooting of SMG bullets when mouse left click is held.
******************************************************************************/
#pragma once

struct PlayerInputOnMouseLeftHeld : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnMouseLeftHeld>
	{
		.m_pName = "PlayerInputOnMouseLeftHeld"
	};

	PlayerInputOnMouseLeftHeld(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		// Is there a way to store player archetype? 
		// Or do I have to query everytime an event happens
		mQueryPlayerOnly.m_Must.AddFromComponents<Position, Velocity, PlayerTag>();
		mQueryPlayerOnly.m_NoneOf.AddFromComponents<Bullet>();

		mBulletPrefabGUID = CreatePrefab<Position, Velocity, Bullet, Timer, GridCell>(
			[&](Position& bulletPos, Timer& timer, Velocity& bulletVel, Bullet& bullet) noexcept
			{
				timer.mValue = 1.f;
			});
	}

	void OnEvent(int mouseX, int mouseY)
	{
		Foreach(Search(mQueryPlayerOnly), [&](const Position& position, Weapon& weapon)
			{
				if (weapon.mState == Weapon::State::RELOAD
				 || weapon.mState == Weapon::State::RELOADING
				 || weapon.mCanShoot == false)
				{
					return;
				}
				
				weapon.mState = Weapon::State::FIRING;

				xcore::vector2 aimDirection
				{
					mouseX - position.x,
					mouseY - position.y
				};

				Shoot(weapon, position, aimDirection.NormalizeSafe());
			});
	}

private:
	void Shoot(
		Weapon& weapon,
		const Position& playerPos,
		const xcore::vector2& aimDirection)
	{
		std::visit(
			overload
			{
				[&](const SubmachineGun& smg) noexcept
				{
					CreatePrefabInstance(1, mBulletPrefabGUID, 
						[&](Position& bulletPos, Timer& timer, Velocity& bulletVel, Bullet& bullet)
						{
							bulletPos = playerPos;

							auto newDirection = aimDirection;
							auto randomAngle = xcore::math::DegToRad(Math::UniformRand(1.f, 15.f));

							newDirection.Rotate(xcore::math::radian(static_cast<long double>(randomAngle)));
							newDirection.NormalizeSafe();

							bullet.mDamage = smg.GetDamage();
							bullet.mPushback = smg.GetPushback();

							bulletVel.mValue = newDirection * 5.f;

							SendGlobalEvent<PlaySound>(SMG_SHOT_SOUND, SMG_SHOT_SOUND_VOL);
						});

					weapon.Shoot();
				},
				[&](const auto&) noexcept
				{
					// do nothing
				}
			}, weapon.mArsenal[static_cast<int>(weapon.mCurrentWeapon)]
		);
	}

private:
	xecs::query::instance mQueryPlayerOnly{};

	xecs::prefab::guid mBulletPrefabGUID{};
};