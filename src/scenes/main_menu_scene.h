#pragma once

struct MainMenuScene : public Scene<MainMenuScene>
{
	MainMenuScene(Game& game)
		: Scene{ game }
	{
	}

	void Load() noexcept
	{
		mManager = std::make_unique<Scene::Manager>();

		RegisterComponents();
		RegisterEvents();
		RegisterSystems();
	}

	void RegisterComponents() noexcept
	{
		mManager->RegisterComponents
			<
			// Data
			Position,
			Colour,
			Scale,
			Timer,
			Text,
			Button,
			// Share
			ButtonDetails
			> ();
	}

	void RegisterSystems() noexcept
	{
		mManager->RegisterSystems
			<
			UpdateTimer,
			ButtonLogic,
			Renderer,
				RenderButtons,
				RenderText
			> ();

		mManager->RegisterSystems
			<
				ButtonOnMouseMove
			>();
	}

	void RegisterEvents()
	{
		mManager->RegisterGlobalEvents
			<
			OnKeyTriggered,
			OnKeyDown,
			OnKeyUp,
			OnMouseLeftClicked,
			OnMouseLeftHeld,
			OnMouseLeftReleased,
			OnMouseMove
			>();
	}
};