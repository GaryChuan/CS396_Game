#pragma once

template <typename T>
struct WeaponInterface : CRTP<T>
{
public:
	float GetDamage() const { return mDamage; }
	unsigned GetAmmo() const { return mAmmo; }

protected:
	WeaponInterface(float damage, unsigned ammo)
		: mDamage{ damage }
		, mAmmo { ammo }
	{
	}

protected:
	float mDamage;
	unsigned mAmmo;
};

struct Shotgun : public WeaponInterface<Shotgun>
{
public:
	Shotgun()  : WeaponInterface{ 10, 4u } {}
};

struct Pistol : public WeaponInterface<Shotgun>
{
public:
	Pistol() : WeaponInterface{ 5, 10u } {}
};

struct SubmachineGun : public WeaponInterface<Shotgun>
{
public:
	SubmachineGun() : WeaponInterface{ 3, 30u } {}
};

using WeaponType = std::variant<Shotgun, Pistol, SubmachineGun>;

struct Weapon
{
	constexpr static auto typedef_v =
		xecs::component::type::data
		{
			.m_pName = "Weapon"
		};
	 
	int mIndex{ 0 }; // Used for swapping weapons
	WeaponType mType{ Pistol{} };
};