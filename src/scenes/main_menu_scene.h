#pragma once

struct MainMenuScene : public Scene<MainMenuScene>
{
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
			PlayerInputOnKeyTriggered,
			PlayerInputOnKeyDown,
			PlayerInputOnKeyUp,
			PlayerInputOnMouseLeftClicked,
			PlayerInputOnMouseLeftHeld,
			PlayerInputOnMouseLeftReleased,
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