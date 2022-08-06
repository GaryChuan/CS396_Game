#include <iostream>
#include "pch.h"
#include "global_settings.h"

#include "components/_components.h"
#include "tools/tools.h"
#include "events/events.h"
#include "systems/_systems.h"

class Game
{
public:
	using Manager = xecs::game_mgr::instance;

	Game(int width = 1024, int height = 800) noexcept
		: mResolution{ 1024, 800 }
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
		//auto PrefabGuid = mManager->CreatePrefab<Position, Velocity, GridCell, Zombie, RenderDetails, Health>(
		//	[&](
		//		Position& pos,
		//		Velocity& vel,
		//		Health& health,
		//		GridCell& gridCell,
		//		RenderDetails& renderDetails,
		//		Zombie& zombie) noexcept
		//	{
		//		pos.mValue = xcore::vector2
		//		{
		//			static_cast<float>(std::rand() % mResolution.first),
		//			static_cast<float>(std::rand() % mResolution.second)
		//		};

		//		// vel.x = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
		//		// vel.y = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
		//		// vel.mValue.Normalize();

		//		gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);

		//		renderDetails.mColour = Colour{ 0, 255, 0 };
		//		renderDetails.mSize = Size{ 3 , 3 };

		//		health.mValue = 100;
		//		//Timer.m_Value = 0;
		//	});

		////auto PrefabVariantGuid = mManager->CreatePrefabVariant(PrefabGuid, [&](Position& pos, Velocity& vel) noexcept
		////	{
		////		// Timer.m_Value = std::rand() / static_cast<float>(RAND_MAX) * 8;
		////	});


		//mManager->CreatePrefabInstance(100, PrefabGuid,
		//	[&](
		//		Position& pos,
		//		Velocity& vel,
		//		GridCell& gridCell,
		//		RenderDetails& renderDetails,
		//		Health& health,
		//		const Zombie& zombie) noexcept
		//	{
		//		pos.mValue = xcore::vector2
		//		{
		//			static_cast<float>(std::rand() % mResolution.first),
		//			static_cast<float>(std::rand() % mResolution.second)
		//		};

		//		gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);

		//		renderDetails.mColour = Colour{ 0, 1, 0 };
		//		renderDetails.mSize = Size{ 3 , 3 };
		//		// Timer.m_Value = std::rand() / static_cast<float>(RAND_MAX) * 8;
		//	});
	}

	void Run() noexcept
	{
		if (mMouseButtonState[GLUT_LEFT_BUTTON] == GLUT_DOWN)
		{
			mManager->SendGlobalEvent<OnMouseLeftHeld>(mMousePos.first, mMousePos.second);
		}

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

	void OnMouseMotion(int mouseX, int mouseY) noexcept
	{
		mMousePos.first = mouseX;
		mMousePos.second = mouseY;
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
			OnKeyTriggered,
			OnKeyDown,
			OnKeyUp,
			OnMouseLeftClicked,
			OnMouseLeftHeld,
			OnMouseLeftReleased
			>();
	}

	void RegisterComponents()
	{
		assert(mManager);

		mManager->RegisterComponents
			<
			// Data
			Position,
			Velocity,
			Colour,
			Scale,
			Weapon,
			Bullet,
			Zombie,
			Health,
			Timer,
			Text,
			Button,
			// Share
			GridCell,
			ZombieDetails,
			ButtonDetails,
			ZombieWave,
			// Tag
			PlayerTag,
			ParticleTag,
			SpawnZombieWaveDetails
			>();
	}

	void RegisterSystems()
	{
		assert(mManager);

		mManager->RegisterSystems
			<
			UpdateMovement,
			UpdateParticles,
			ClampMovement,
			UpdateTimer,
			PlayerLogic,
			BulletLogic,
			ZombieLogic,
				ZombieSteeringLogic,
				ZombieUpdateVelocity,
			ZombieWaveLogic,
			ZombieWaveSpawnTimerLogic,
			Renderer,
				// RenderGrid,
				RenderPlayer,
				RenderZombies,
				RenderBullets,
				RenderParticles,
				RenderButtons,
				RenderText
			>();

		mManager->RegisterSystems
			<
				SpawnParticleOnZombieDeath,
				SpawnParticleOnZombieHit,
				StartTimerOnZombieWaveCleared,
				SpawnZombieWaveOnTimerEnd,
				PlayerInputOnKeyTriggered,
				PlayerInputOnKeyDown,
				PlayerInputOnKeyUp,
				PlayerInputOnMouseLeftClicked,
				PlayerInputOnMouseLeftHeld,
				PlayerInputOnMouseLeftReleased,
				PlayerDeactivateTextOnRemoveTimer,
				DestroyBulletOnRemoveTimer,
				DestroyParticleOnRemoveTimer,
				ZombieRestoreColourOnRemoveTimer
			>();
	}

private:
	std::unique_ptr<Manager> mManager{};
	std::pair<int, int> mResolution{};
	std::pair<int, int> mMousePos{};
	std::array<int, 3> mMouseButtonState{ GLUT_UP, GLUT_UP, GLUT_UP };
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

//---------------------------------------------------------------------------------------
// GLUT TOGGLE MAXIMIZE BUTTON
//---------------------------------------------------------------------------------------
void toggleGlutWindowMaximizeBox(LPCWSTR szWindowTitle)
{
	long dwStyle;
	HWND hwndGlut;

	hwndGlut = FindWindow(NULL, szWindowTitle);

	dwStyle = GetWindowLong(hwndGlut, GWL_STYLE);
	dwStyle ^= WS_MAXIMIZEBOX;
	SetWindowLong(hwndGlut, GWL_STYLE, dwStyle);
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
	glutCreateWindow("Topdown Shooter");
	toggleGlutWindowMaximizeBox(L"Topdown Shooter");

	glutDisplayFunc([](void) noexcept
		{
			game.Run();
		});
	glutReshapeFunc([](int, int) noexcept
		{
			// Prevent resizing (fix height/width)
			const auto& [width, height] = game.GetResolution();
			glutReshapeWindow(width, height);
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
	glutMotionFunc([](int mouseX, int mouseY) noexcept
		{
			game.OnMouseMotion(mouseX, mouseY);
		});
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

	return 0;
}