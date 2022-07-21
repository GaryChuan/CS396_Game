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
				Position, Input
			>();
	}

	void RegisterSystems()
	{
		mManager->RegisterSystems
			<
				Renderer
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

    //
    // Create the graphics and main loop
    //
    glutInitWindowSize(width, height);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("xECS Live Coding Example");

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