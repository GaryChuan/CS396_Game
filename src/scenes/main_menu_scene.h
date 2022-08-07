#pragma once

struct MainMenuScene : public Scene<MainMenuScene>
{
	MainMenuScene(GameStateManager& gsm)
		: Scene{ gsm }
	{
	}

	void Load() noexcept
	{
		mManager = std::make_unique<Scene::Manager>();

		RegisterComponents();
		RegisterEvents();
		RegisterSystems();

		InitializeScene();
	}

private:
	void InitializeScene() noexcept
	{
		auto& buttonArchetype = mManager->getOrCreateArchetype<ButtonArchetype>();

		buttonArchetype.CreateEntity(
			[&](Position& pos, Colour& colour, Scale& scale, Text& text, Button& button, ButtonDetails& buttonDetails)
			{
				text.mActive = true;
				text.mValue = "START";

				text.mOffset.mValue = xcore::vector2{ -20, 2.75f };

				text.mFont = Text::Font::HELVETICA_12;
				text.mColour.mValue = xcore::vector3{ 0, 0, 0 };

				pos.x = Grid::MAX_RESOLUTION_WIDTH / 2;
				pos.y = Grid::MAX_RESOLUTION_HEIGHT / 2;

				button.mCallback = std::bind(&MainMenuScene::SetNextScene, this);

				colour.mValue = buttonDetails.mButtonColours[Button::State::DEFAULT];
				scale.mValue = xcore::vector2{ 30, 10 };
			});
	}

	void SetNextScene() noexcept
	{
		mGSM.get().SetNextScene(SceneState::GAME);
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