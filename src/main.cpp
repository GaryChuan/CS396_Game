#include <iostream>
#include "pch.h"

#include "components/components.h"
#include "events/events.h"
#include "systems/systems.h"

class Game
{
public:
	using Manager = xecs::game_mgr::instance;

	Game(int width = 1024, int height = 800) noexcept
		: mResolution { 1024, 800 }
	{
		Initialize();
	}

	~Game()
	{
		xcore::Kill();
	}

	void CreateDefaultScene() noexcept
	{
		assert(mManager);

		std::srand(101);

		// Enemy prefabs
		//auto PrefabGuid = mManager->CreatePrefab<Position, Velocity, Health>([&](Position& pos, Velocity& vel, Health& health) noexcept
		//	{
		//		pos.mValue = xcore::vector2
		//		{ 
		//			static_cast<float>(std::rand() % mResolution.first),
		//			static_cast<float>(std::rand() % mResolution.second)
		//		};

		//		vel.x = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
		//		vel.y = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
		//		vel.mValue.Normalize();

		//		health.mValue = 100;
		//		//Timer.m_Value = 0;
		//	});

		////auto PrefabVariantGuid = mManager->CreatePrefabVariant(PrefabGuid, [&](Position& pos, Velocity& vel) noexcept
		////	{
		////		// Timer.m_Value = std::rand() / static_cast<float>(RAND_MAX) * 8;
		////	});


		//mManager->CreatePrefabInstance(2000, PrefabGuid, [&](Position& pos, Velocity& vel, Health& health) noexcept
		//	{
		//		pos.mValue = xcore::vector2
		//		{ 
		//			static_cast<float>(std::rand() % mResolution.first), 
		//			static_cast<float>(std::rand() % mResolution.second)
		//		};

		//		vel.x = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
		//		vel.y = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
		//		vel.mValue.Normalize();

		//		// Timer.m_Value = std::rand() / static_cast<float>(RAND_MAX) * 8;
		//	});
	}

	void Run() noexcept
	{
		mManager->Run();
	}

	void SetResolution(int width, int height)
	{
		auto& [mWidth, mHeight] = mResolution;

		mWidth = width;
		mHeight = height;
	}

	const std::pair<int, int>& GetResolution() const
	{
		return mResolution;
	}

	void OnKeyboardDown(unsigned char key, int mouseX, int mouseY) noexcept
	{
		mKeys[static_cast<std::uint8_t>(key)] = true;
		mManager->SendGlobalEvent<OnKeyDown>(mKeys);
	}

	void OnKeyboardUp(unsigned char key, int mouseX, int mouseY) noexcept
	{
		mKeys[static_cast<std::uint8_t>(key)] = false;
		mManager->SendGlobalEvent<OnKeyUp>(mKeys);
	}

	void OnMouseClick(int button, int state, int mouseX, int mouseY) noexcept
	{
		bool clicked = state == GLUT_DOWN;

		if (!clicked)
		{
			return;
		}

		if (button == GLUT_LEFT_BUTTON)
		{
			mManager->SendGlobalEvent<OnMouseLeftClick>(mouseX, mouseY);
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			mManager->SendGlobalEvent<OnMouseRightClick>(mouseX, mouseY);
		}
	}

private:
	void Initialize() noexcept
	{
		xcore::Init("ECS Example");

		mManager = std::make_unique<Manager>();

		RegisterComponents();
		RegisterEvents();
		RegisterSystems();
	}

	void RegisterEvents()
	{
		assert(mManager);

		mManager->RegisterGlobalEvents
			<
				OnKeyDown,
				OnKeyUp,
				OnMouseLeftClick
			>();
	}

	void RegisterComponents()
	{
		assert(mManager);

		mManager->RegisterComponents
			<
				Position, 
				Velocity, 
				Bullet, 
				Health, 
				Timer,
				PlayerTag
			>();
	}

	void RegisterSystems()
	{
		assert(mManager);

		mManager->RegisterSystems
			<
				UpdateMovement,
				PlayerLogic,
				BulletLogic,
				Renderer,
					RenderCharacters,
					RenderBullets
			>();

		mManager->RegisterSystems
			<
				PlayerInputOnKeyDown,
				PlayerInputOnKeyUp,
				PlayerInputOnMouseLeftClick
			>();
	}

private:
	std::unique_ptr<Manager> mManager{};
	std::pair<int, int> mResolution{};
	Keys mKeys{};
};

//---------------------------------------------------------------------------------------
// GLUT TIMER
//---------------------------------------------------------------------------------------

void timer(int value) noexcept
{
	// Post re-paint request to activate display()
	glutPostRedisplay();

	// next timer call milliseconds later
	glutTimerFunc(15, timer, 0);
}


int main(int argc, char** argv)
{
	static Game game{};

	const auto& [width, height] = game.GetResolution();

	game.CreateDefaultScene();

	//
	// Create the graphics and main loop
	//
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("CS396 Game");

	glutDisplayFunc([](void) noexcept
		{
			game.Run();
		});
	glutReshapeFunc([](int w, int h) noexcept
		{
			game.SetResolution(w, h);
		});
	glutKeyboardFunc([](unsigned char key, int mouseX, int mouseY) noexcept
		{
			game.OnKeyboardDown(key, mouseX, mouseY);
		});
	glutKeyboardUpFunc([](unsigned char key, int mouseX, int mouseY) noexcept
		{
			game.OnKeyboardUp(key, mouseX, mouseY);
		});
	glutMouseFunc([](int button, int state, int mouseX, int mouseY) noexcept
		{
			game.OnMouseClick(button, state, mouseX, mouseY);
		});
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

	return 0;
}