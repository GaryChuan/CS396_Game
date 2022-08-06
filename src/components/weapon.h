#pragma once

struct Weapon;

template <typename T>
struct WeaponInterface : CRTP<T>
{
public:
	float GetDamage() const noexcept { return mDamage; }
	unsigned GetMaxAmmoCount() const noexcept { return mMaxAmmoCount; }
	unsigned GetAmmoCount() const noexcept { return mAmmoCount; }
	float GetReloadRate() const noexcept { return mReloadRate; }
	float GetPushback() const noexcept { return mPushback; }
	void Reloaded() noexcept { mAmmoCount = mMaxAmmoCount; }

protected:
	WeaponInterface(float damage, float reloadRate, float fireRate, float pushback, unsigned ammoCount)
		: mDamage		{ damage }
		, mPushback		{ pushback }
		, mFireRate		{ fireRate }
		, mReloadRate	{ reloadRate }
		, mMaxAmmoCount	{ ammoCount }
		, mAmmoCount	{ mMaxAmmoCount }
	{
	}

protected:
	friend Weapon;

	float mDamage{};
	float mPushback{};
	float mFireRate{};
	float mReloadRate{};
	unsigned mMaxAmmoCount{};
	unsigned mAmmoCount{};
};

struct Shotgun : public WeaponInterface<Shotgun>
{
public:
	Shotgun() : WeaponInterface { 8, 2, 0.5f, 5.f, 2u } {}
};

struct Pistol : public WeaponInterface<Pistol>
{
public:
	Pistol() : WeaponInterface{ 5, 1, 1, 2.5f, 10u } {}
};

struct SubmachineGun : public WeaponInterface<SubmachineGun>
{
public:
	SubmachineGun() : WeaponInterface{ 3, 3, 0.1f, 2.f, 30u } {}
};

using WeaponType = std::variant<Pistol, Shotgun, SubmachineGun>;

struct Weapon
{
	using Arsenal = std::array<WeaponType, std::variant_size_v<WeaponType>>;

	constexpr static auto names = std::array{ "Pistol", "Shotgun", "SMG" };

	constexpr static auto typedef_v =
		xecs::component::type::data
		{
			.m_pName = "Weapon"
		};

	enum struct Type { PISTOL, SHOTGUN, SUBMACHINEGUN };
	enum struct State { RELOAD, RELOADING, SWAPPING, FIRING, INACTIVE };

	unsigned GetAmmoCount() const
	{
		return std::visit
		(
			[](const auto& weaponType) 
			{ 
				return weaponType.mAmmoCount; 
			}, mArsenal[static_cast<int>(mCurrentWeapon)]
		);
	}

	void Shoot()
	{
		assert(mState != Weapon::State::RELOAD);
		assert(mState != Weapon::State::RELOADING);

		if (mCanShoot == false)
		{
			return;
		}

		std::visit
		(
			[&](auto& weaponType)
			{
				assert(weaponType.mAmmoCount);

				--weaponType.mAmmoCount;

				if (weaponType.mAmmoCount <= 0)
				{
					mState = State::RELOAD;
				}
			}, mArsenal[static_cast<int>(mCurrentWeapon)]
		);

		mCanShoot = false;
	}

	void Reloaded()
	{
		std::visit
		(
			[](auto& weaponType)
			{
				weaponType.Reloaded();
			}, mArsenal[static_cast<int>(mCurrentWeapon)]
		);
	}

	float GetReloadRate() const
	{
		return std::visit
		(
			[](const auto& weaponType) noexcept
			{
				return weaponType.mReloadRate;
			}, mArsenal[static_cast<int>(mCurrentWeapon)]
		);
	}
	
	float GetFireRate() const
	{
		return std::visit
		(
			[](const auto& weaponType) noexcept
			{
				return weaponType.mFireRate;
			}, mArsenal[static_cast<int>(mCurrentWeapon)]
		);
	}

	float GetDamage() const
	{
		return std::visit
		(
			[](const auto& weaponType) noexcept
			{
				return weaponType.mDamage;
			}, mArsenal[static_cast<int>(mCurrentWeapon)]
		);
	}

	float GetPushback() const
	{
		return std::visit
		(
			[] (const auto& weaponType) noexcept
			{
				return weaponType.mPushback;
			}, mArsenal[static_cast<int>(mCurrentWeapon)]
		);
	}

	float mShootTimer = 0.f;
	float mReloadTimer = 0.f;
	bool mCanShoot = true;
	Type mCurrentWeapon = Type::PISTOL;
	State mState{ State::INACTIVE };
	Arsenal mArsenal{ Pistol{}, Shotgun{}, SubmachineGun{} };
};