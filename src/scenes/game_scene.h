#pragma once

struct GameScene : public Scene<GameScene>
{
	GameScene(Game& game)
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

private:
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
			OnMouseLeftReleased,
			OnMouseMove
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
			ButtonLogic,
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
				ButtonOnMouseMove,
				DestroyBulletOnRemoveTimer,
				DestroyParticleOnRemoveTimer,
				ZombieRestoreColourOnRemoveTimer
			>();
	}
};