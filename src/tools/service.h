#pragma once


template <typename T, typename ... Args>
constexpr std::unique_ptr<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
struct Service
{
public:

	template <typename... TArgs>
	static void Register(TArgs&& ...args)
	{
		assert(!mService);

		mService = std::make_unique<T>(std::forward<TArgs>(args)...);
	}

	static void Release()
	{
		assert(mService);

		mService.reset();
	}

	static T& Get() noexcept
	{
		assert(mService);

		return *mService;
	}

private:
	__inline static std::unique_ptr<T> mService{};
};