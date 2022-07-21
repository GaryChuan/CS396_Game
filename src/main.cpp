#include <iostream>
#include "pch.h"

#include "components/components.h"
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

		auto PrefabGuid = mManager->CreatePrefab<Position, Velocity>([&](Position& pos, Velocity& vel) noexcept
			{
				pos.mValue = xcore::vector2
				{ 
					static_cast<float>(std::rand() % mResolution.first),
					static_cast<float>(std::rand() % mResolution.second)
				};

				vel.x = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
				vel.y = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
				vel.mValue.Normalize();

				//Timer.m_Value = 0;
			});

		//auto PrefabVariantGuid = mManager->CreatePrefabVariant(PrefabGuid, [&](Position& pos, Velocity& vel) noexcept
		//	{
		//		// Timer.m_Value = std::rand() / static_cast<float>(RAND_MAX) * 8;
		//	});


		mManager->CreatePrefabInstance(2000, PrefabGuid, [&](Position& pos, Velocity& vel) noexcept
			{
				pos.mValue = xcore::vector2
				{ 
					static_cast<float>(std::rand() % mResolution.first), 
					static_cast<float>(std::rand() % mResolution.second)
				};

				vel.x = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
				vel.y = std::rand() / static_cast<float>(RAND_MAX) - 0.5f;
				vel.mValue.Normalize();

				// Timer.m_Value = std::rand() / static_cast<float>(RAND_MAX) * 8;
			});
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

private:
	void Initialize() noexcept
	{
		xcore::Init("ECS Example");

		mManager = std::make_unique<Manager>();

		RegisterComponents();
		RegisterSystems();
	}

	void RegisterComponents()
	{
		mManager->RegisterComponents
			<
				Position, Velocity, Input
			>();
	}

	void RegisterSystems()
	{
		mManager->RegisterSystems
			<
				UpdateMovement,
				Renderer,
					RenderCharacters
			>();
	}

private:
	std::unique_ptr<Manager> mManager;
	std::pair<int, int> mResolution;

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
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

	return 0;
}