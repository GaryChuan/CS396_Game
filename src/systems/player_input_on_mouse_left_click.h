#pragma once

struct PlayerInputOnMouseLeftClick : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnMouseLeftClick>
	{
		.m_pName = "PlayerInputOnMouseLeftClick"
	};

	PlayerInputOnMouseLeftClick(xecs::game_mgr::instance& gameMgr)
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

		Foreach(Search(mQueryPlayerOnly), [&](const Position& position, const Weapon& weapon)
			{
				xcore::vector2 aimDirection
				{
					mouseX - position.x,
					mouseY - position.y
				};

				Shoot(weapon.mType, position, aimDirection.NormalizeSafe());
			});
	}

private:
	void Shoot(
		const WeaponType& weaponType, 
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

					std::cout << "Pistol Shoot" << std::endl;
				},
				[&](const Shotgun& shotgun) noexcept
				{
					const long double angle = xcore::math::DegToRad(5.f);
					int i = -2;

					mBulletArchetypePtr->CreateEntities(5, [&](Position& bulletPos, Velocity& bulletVel)
						{
							auto shotDirection = aimDirection;

							shotDirection.Rotate(xcore::math::radian{ angle * i });
							
							bulletPos = playerPos;
							bulletVel.mValue = shotDirection * 5.f;
							
							++i;
						});

					std::cout << "Shotgun Shoot" << std::endl;
				},
				[&](const SubmachineGun& smg) noexcept
				{
					std::cout << "SubmachineGun Shoot" << std::endl;
				}
			}, weaponType
		);
	}

private:
	xecs::archetype::instance* mBulletArchetypePtr{};
	xecs::query::instance mQueryPlayerOnly{};
};