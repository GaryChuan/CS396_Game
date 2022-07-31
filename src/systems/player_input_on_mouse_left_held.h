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

		mBulletArchetypePtr = &getOrCreateArchetype<BulletArchetype>();
	}

	void OnEvent(int mouseX, int mouseY)
	{
		assert(mBulletArchetypePtr);

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
					mBulletArchetypePtr->CreateEntity([&](Position& bulletPos, Velocity& bulletVel)
						{
							bulletPos = playerPos;

							auto newDirection = aimDirection;
							auto randomAngle = xcore::math::DegToRad(Math::UniformRand(1.f, 15.f));

							newDirection.Rotate(xcore::math::radian(static_cast<long double>(randomAngle)));
							newDirection.NormalizeSafe();

							bulletVel.mValue = newDirection * 5.f;
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
	xecs::archetype::instance* mBulletArchetypePtr{};
	xecs::query::instance mQueryPlayerOnly{};
};