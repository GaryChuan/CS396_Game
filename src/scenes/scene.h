#pragma once

template <typename T>
struct Scene : CRTP<T>
{
	using Manager = xecs::game_mgr::instance;

	void OnKeyboardDown(unsigned char key, int mouseX, int mouseY)
	{
		auto& pressed = mKeys[static_cast<std::uint8_t>(key)];

		if (!pressed)
		{
			mManager->SendGlobalEvent<OnKeyTriggered>(mKeys);
			pressed = true;
		}

		mManager->SendGlobalEvent<OnKeyDown>(mKeys);
	}

	void OnKeyboardUp(unsigned char key, int mouseX, int mouseY) noexcept
	{
		mKeys[static_cast<std::uint8_t>(key)] = false;
		mManager->SendGlobalEvent<OnKeyUp>(mKeys);
	}

	void OnMouseClick(int button, int state, int mouseX, int mouseY) noexcept
	{
		// Button is not registered, do not process
		if (button > mMouseButtonState.size())
		{
			return;
		}

		bool clicked = state == GLUT_DOWN;

		if (!clicked)
		{
			mMouseButtonState[button] = GLUT_UP;
			mManager->SendGlobalEvent<OnMouseLeftReleased>(mouseX, mouseY);
			return;
		}

		if (mMouseButtonState[button] == GLUT_UP)
		{
			mMouseButtonState[button] = GLUT_DOWN;

			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				mManager->SendGlobalEvent<OnMouseLeftClicked>(mouseX, mouseY);
				break;

			case GLUT_RIGHT_BUTTON:
				break;

			case GLUT_MIDDLE_BUTTON:
				break;
			default:
				assert(false); // unknown button pressed
			}
		}
	}

	void Load() noexcept
	{
		this->underlying().Load();
	}

	void Run()
	{
		mManager->Run();
	}

	void Unload()
	{
		mManager.reset();
		xecs::component::mgr::resetRegistrations();
	}

	void OnMouseMotion(int mouseX, int mouseY) noexcept
	{
		mMousePos.first = mouseX;
		mMousePos.second = mouseY;
	}

	void OnMousePassiveMotion(int mouseX, int mouseY) noexcept
	{
		mManager->SendGlobalEvent<OnMouseMove>(mouseX, mouseY);
	}

	~Scene()
	{
		std::cout << "End Scene" << std::endl;
	}

protected:
	std::unique_ptr<Manager> mManager{};
	std::pair<int, int> mMousePos{};
	std::array<int, 3> mMouseButtonState{ GLUT_UP, GLUT_UP, GLUT_UP };
	Keys mKeys{};
};
