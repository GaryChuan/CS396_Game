/******************************************************************************
filename: main.cpp
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file is where the Game class is defined and where the main loop runs.
******************************************************************************/
#include <iostream>
#include "pch.h"
#include "global_settings.h"

#include "audio/audio_manager.h"

#include "game_state_manager.h"

#include "components/_components.h"
#include "tools/tools.h"
#include "events/_events.h"
#include "systems/_systems.h"
#include "scenes/_scenes.h"


class Game
{
public:
	using Manager = xecs::game_mgr::instance;

	Game(int width = 1024, int height = 800) noexcept
		: mResolution{ width, height}
	{
		Initialize();
	}

	~Game()
	{
		xcore::Kill();
	}

	void Run() noexcept
	{
		switch (mGameState)
		{
		case GameState::LOAD:
			std::visit([](auto& scene) { scene.Load();  }, mCurrentScene);
			mGameState = GameState::RUN;
			break;
		case GameState::RUN:
			if (mGSM.ChangeScene())
			{
				mGameState = GameState::UNLOAD;
			}
			else
			{
				std::visit([](auto& scene) { scene.Run(); }, mCurrentScene);
			}
			break;
		case GameState::UNLOAD:
			std::visit([](auto& scene) { scene.Unload(); }, mCurrentScene);
			LoadNextScene(mGSM.GetNextScene());
			mGSM.ChangeToNextScene();
			mGameState = GameState::LOAD;
			break;
		}
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
		if (mGameState == GameState::LOAD 
		 || mGameState == GameState::UNLOAD)
		{
			return;
		}

		std::visit(
			[&](auto& scene) { scene.OnKeyboardDown(key, mouseX, mouseY); },
			mCurrentScene);
	}

	void OnKeyboardUp(unsigned char key, int mouseX, int mouseY) noexcept
	{
		if (mGameState == GameState::LOAD
		 || mGameState == GameState::UNLOAD)
		{
			return;
		}

		std::visit(
			[&](auto& scene) { scene.OnKeyboardUp(key, mouseX, mouseY); },
			mCurrentScene);
	}

	void OnMouseClick(int button, int state, int mouseX, int mouseY) noexcept
	{
		if (mGameState == GameState::LOAD
		 || mGameState == GameState::UNLOAD)
		{
			return;
		}

		std::visit(
			[&](auto& scene) { scene.OnMouseClick(button, state, mouseX, mouseY); },
			mCurrentScene);
	}

	void OnMouseMotion(int mouseX, int mouseY) noexcept
	{
		if (mGameState == GameState::LOAD
		 || mGameState == GameState::UNLOAD)
		{
			return;
		}

		std::visit(
			[&](auto& scene) { scene.OnMouseMotion(mouseX, mouseY); },
			mCurrentScene);
	}

	void OnMousePassiveMotion(int mouseX, int mouseY) noexcept
	{
		if (mGameState == GameState::LOAD
		 || mGameState == GameState::UNLOAD)
		{
			return;
		}

		std::visit(
			[&](auto& scene) { scene.OnMousePassiveMotion(mouseX, mouseY); }, 
			mCurrentScene);
	}

private:
	using Scenes = std::variant<MainMenuScene, GameScene, RetryMenuScene>;

	void Initialize() noexcept
	{
		xcore::Init("ECS Example");
	}

	void LoadNextScene(SceneState nextScene)
	{
		switch (nextScene)
		{
		case SceneState::MAIN_MENU:
			mCurrentScene = MainMenuScene{ mGSM };
			break;
		case SceneState::GAME:
			mCurrentScene = GameScene{ mGSM };
			break;
		case SceneState::RETRY_MENU:
			mCurrentScene = RetryMenuScene{ mGSM };
			break;
		}
	}
	
private:
	GameStateManager mGSM{};
	Scenes mCurrentScene{std::in_place_index<0>, mGSM};
	GameState mGameState{ GameState::LOAD };
	SceneState mNextScene{ SceneState::MAIN_MENU };

	std::pair<int, int> mResolution{};
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

//---------------------------------------------------------------------------------------
// INTIALIZE ALL AUDIO
//---------------------------------------------------------------------------------------
void InitializeAudio()
{
	auto& audioManager = Service<AudioManager>::Get();
	
	audioManager.Initialize();

	audioManager.CreateSound(BGM, "../../resources/BGM.wav");
	audioManager.CreateSound(PISTOL_SHOT_SOUND, "../../resources/pistol_shot.wav");
}


int main(int argc, char** argv)
{
	static Game game{};

	Service<AudioManager>::Register();

	const auto& [width, height] = game.GetResolution();

	// Initialize audio -- adding sounds etc..
	InitializeAudio();

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
			Service<AudioManager>::Get().Update();
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

	glutPassiveMotionFunc([](int mouseX, int mouseY)
		{
			game.OnMousePassiveMotion(mouseX, mouseY);
		});

	glutMotionFunc([](int mouseX, int mouseY) noexcept
		{
			game.OnMouseMotion(mouseX, mouseY);
		});
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

	Service<AudioManager>::Release();

	return 0;
}