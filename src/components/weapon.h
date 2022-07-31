#pragma once

struct Weapon;

template <typename T>
struct WeaponInterface : CRTP<T>
{
public:
	float GetDamage() const { return mDamage; }
	unsigned GetMaxAmmoCount() const { return mMaxAmmoCount; }
	unsigned GetAmmoCount() const { return mAmmoCount; }
	float GetReloadRate() const { return mReloadRate; }
	void Reloaded() { mAmmoCount = mMaxAmmoCount; }

protected:
	WeaponInterface(float damage, float reloadRate, unsigned ammoCount)
		: mDamage		{ damage }
		, mReloadRate	{ reloadRate }
		, mMaxAmmoCount	{ ammoCount }
		, mAmmoCount	{ mMaxAmmoCount }
	{
	}

protected:
	friend Weapon;

	float mDamage{};
	float mReloadRate{};
	unsigned mMaxAmmoCount{};
	unsigned mAmmoCount{};
};

struct Shotgun : public WeaponInterface<Shotgun>
{
public:
	Shotgun()  : WeaponInterface{ 10, 2, 4u } {}
};

struct Pistol : public WeaponInterface<Shotgun>
{
public:
	Pistol() : WeaponInterface{ 5, 1, 10u } {}
};

struct SubmachineGun : public WeaponInterface<Shotgun>
{
public:
	SubmachineGun() : WeaponInterface{ 3, 3, 30u } {}
};

using WeaponType = std::variant<Shotgun, Pistol, SubmachineGun>;

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
				return weaponType.GetAmmoCount(); 
			}, mArsenal[static_cast<int>(mCurrentWeapon)]
		);
	}

	void Shoot()
	{
		assert(mState != Weapon::State::RELOAD);
		assert(mState != Weapon::State::RELOADING);

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
			[](auto& weaponType)
			{
				return weaponType.mReloadRate;
			}, mArsenal[static_cast<int>(mCurrentWeapon)]
		);
	}

	float mReloadTimer = 0.f;
	Type mCurrentWeapon = Type::PISTOL;
	State mState{ State::INACTIVE };
	Arsenal mArsenal{ Pistol{}, Shotgun{}, SubmachineGun{} };
};