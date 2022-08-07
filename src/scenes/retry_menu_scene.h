/******************************************************************************
filename: retry_menu_scene.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of RetryMenuScene.
******************************************************************************/
#pragma once

struct RetryMenuScene : public Scene<RetryMenuScene>
{
	RetryMenuScene(GameStateManager& gsm)
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

		Service<AudioManager>::Get().StopAllChannels();
	}

	void Unload() noexcept
	{
		Release();
	}

private:
	void InitializeScene() noexcept
	{
		auto& buttonArchetype = mManager->getOrCreateArchetype<ButtonArchetype>();

		constexpr xcore::vector2 center{ Grid::MAX_RESOLUTION_WIDTH / 2, Grid::MAX_RESOLUTION_HEIGHT / 2 };

		buttonArchetype.CreateEntity(
			[&](Position& pos, Colour& colour, Scale& scale, Text& text, Button& button, ButtonDetails& buttonDetails)
			{
				text.mActive = true;
				text.mValue = "RETRY";

				text.mOffset.mValue = xcore::vector2{ -20, 2.75f };

				text.mFont = Text::Font::HELVETICA_12;
				text.mColour.mValue = xcore::vector3{ 0, 0, 0 };

				pos.mValue = center;

				button.mCallback = std::bind(&Scene::SetNextScene, this, SceneState::GAME);

				colour.mValue = buttonDetails.mButtonColours[Button::State::DEFAULT];
				scale.mValue = xcore::vector2{ 30, 10 };
			});

		buttonArchetype.CreateEntity(
			[&](Position& pos, Colour& colour, Scale& scale, Text& text, Button& button, ButtonDetails& buttonDetails)
			{
				text.mActive = true;
				text.mValue = "BACK";

				text.mOffset.mValue = xcore::vector2{ -20, 2.75f };

				text.mFont = Text::Font::HELVETICA_12;
				text.mColour.mValue = xcore::vector3{ 0, 0, 0 };

				pos.mValue = center;
				pos.y += 50.f;

				button.mCallback = std::bind(&Scene::SetNextScene, this, SceneState::MAIN_MENU);

				colour.mValue = buttonDetails.mButtonColours[Button::State::DEFAULT];
				scale.mValue = xcore::vector2{ 30, 10 };
			});
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
			>();
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
			>();

		mManager->RegisterSystems
			<
			ButtonOnMouseMove,
			ButtonOnLeftMouseClicked,
			ButtonOnLeftMouseReleased
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