#pragma once

template <typename T>
constexpr T PI = static_cast<T>(3.1415926535897932384626433833);

template <typename T>
constexpr T TAU = 2 * PI<T>;

static std::mt19937 prng{ std::random_device{}() };

template <typename T>
inline static T UniformRand(T min, T max)
{
	if (min > max)
		return UniformRand(max, min);
	else if constexpr (std::is_floating_point_v<T>)
		return std::uniform_real_distribution<T>{min, max}(prng);
	else
		return std::uniform_int_distribution<T>{min, max}(prng);
}

inline static xcore::vector2 UniformRandVec2(const xcore::vector2& min, const xcore::vector2& max)
{
	return xcore::vector2
	{
		UniformRand(min.m_X, max.m_X),
		UniformRand(min.m_Y, max.m_Y)
	};
}

template <typename T>
inline static xcore::vector2 DiskRand(T radius)
{
	xcore::vector3 result = xcore::vector3::ZERO;

	if (radius <= static_cast<T>(0))
		return result;

	float radius2 = radius * radius;
	float length2 = 0;

	const auto min = xcore::vector2{ -radius, -radius };
	const auto max = xcore::vector2{ radius, radius };

	do
	{
		result = std::move(UniformRandVec2(min, max));
		length2 = result.getLengthSquared();

	} while (length2 > radius2);

	return result;
}
template <typename T>
inline static xcore::vector2 UniformDiskRand(T radius)
{
	xcore::vector2 result{};
	constexpr T one = static_cast<T>(1);
	constexpr T zero = static_cast<T>(0);

	if (radius > static_cast<T>(0))
	{
		T u = UniformRand(zero, one) + UniformRand(zero, one);
		T r = u > 1 ? 2 - u : u;
		T theta = UniformRand(static_cast<T>(0), TAU<T>);

		result.m_X = r * std::cos(theta);
		result.m_Y = r * std::sin(theta);
	}

	return result;
}