/******************************************************************************
filename: player_input_on_mouse_left_clicked.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of PlayerInputOnMouseLeftClicked which handles
  shooting of all wepaon bullets when mouse left click is pressed.
******************************************************************************/
#pragma once

struct PlayerInputOnMouseLeftClicked : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnMouseLeftClicked>
	{
		.m_pName = "PlayerInputOnMouseLeftClicked"
	};

	PlayerInputOnMouseLeftClicked(xecs::game_mgr::instance& gameMgr)
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

		mBulletArchetypePtr = &getOrCreateArchetype<BulletArchetype>();
	}

	void OnEvent(int mouseX, int mouseY)
	{
		Foreach(Search(mQueryPlayerOnly), [&](const Position& position, Weapon& weapon)
			{
				if (weapon.mState == Weapon::State::RELOAD 
				 || weapon.mState == Weapon::State::RELOADING)
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
				[&](const Pistol& pistol) noexcept 
				{
					CreatePrefabInstance(1, mBulletPrefabGUID,
						[&](Position& bulletPos, Timer& timer, Velocity& bulletVel, Bullet& bullet)
						{
							bulletPos = playerPos;
							bulletVel.mValue = aimDirection * 5.f;

							bullet.mDamage = pistol.GetDamage();
							bullet.mPushback = pistol.GetPushback();

							timer.mValue = 1.2f;

							SendGlobalEvent<PlaySound>(PISTOL_SHOT_SOUND, PISTOL_SHOT_SOUND_VOL);
						});
				},
				[&](const Shotgun& shotgun) noexcept
				{
					int i = -2;

					mBulletArchetypePtr->CreateEntities(
						5, [&](Position& bulletPos, Timer& timer, Velocity& bulletVel, Bullet& bullet)
						{
							auto shotDirection = aimDirection;
							auto randomAngle = xcore::math::DegToRad(Math::UniformRand(3.f, 5.f));

							shotDirection.Rotate(xcore::math::radian{ randomAngle * i });
							shotDirection.NormalizeSafe();
							
							timer.mValue = 0.8f;

							bullet.mDamage = shotgun.GetDamage();
							bullet.mPushback = shotgun.GetPushback();

							bulletPos = playerPos;
							bulletVel.mValue = shotDirection * Math::UniformRand(4.f, 5.f);
							
							++i;
						});

					SendGlobalEvent<PlaySound>(SHOTGUN_SHOT_SOUND, SHOTGUN_SHOT_SOUND_VOL);
				},
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
				}
			}, weapon.mArsenal[static_cast<int>(weapon.mCurrentWeapon)]
		);

		weapon.Shoot();
	}

private:
	xecs::archetype::instance* mBulletArchetypePtr{};
	xecs::query::instance mQueryPlayerOnly{};

	xecs::prefab::guid mBulletPrefabGUID{};

};