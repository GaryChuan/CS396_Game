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

		mBulletArchetypePtr = &getOrCreateArchetype<BulletArchetype>();
	}

	void OnEvent(int mouseX, int mouseY)
	{
		assert(mBulletArchetypePtr);

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
					mBulletArchetypePtr->CreateEntity([&](Position& bulletPos, Velocity& bulletVel)
						{
							bulletPos = playerPos;
							bulletVel.mValue = aimDirection * 5.f;
						});
				},
				[&](const Shotgun& shotgun) noexcept
				{
					int i = -2;

					mBulletArchetypePtr->CreateEntities(5, [&](Position& bulletPos, Velocity& bulletVel)
						{
							auto shotDirection = aimDirection;
							auto randomAngle = xcore::math::DegToRad(Math::UniformRand(3.f, 5.f));

							shotDirection.Rotate(xcore::math::radian{ randomAngle * i });
							shotDirection.NormalizeSafe();
							
							bulletPos = playerPos;
							bulletVel.mValue = shotDirection * Math::UniformRand(4.f, 5.f);
							
							++i;
						});
				},
				[&](const SubmachineGun& smg) noexcept
				{
					mBulletArchetypePtr->CreateEntity([&](Position& bulletPos, Velocity& bulletVel)
						{
							bulletPos = playerPos;

							auto newDirection = aimDirection;
							auto randomAngle = xcore::math::DegToRad(Math::UniformRand(1.f, 15.f));

							newDirection.Rotate(xcore::math::radian(static_cast<long double>(randomAngle)));
							newDirection.NormalizeSafe();

							bulletVel.mValue = newDirection * 5.f;
						});
				}
			}, weapon.mArsenal[static_cast<int>(weapon.mCurrentWeapon)]
		);

		weapon.Shoot();
	}

private:
	xecs::archetype::instance* mBulletArchetypePtr{};
	xecs::query::instance mQueryPlayerOnly{};

};