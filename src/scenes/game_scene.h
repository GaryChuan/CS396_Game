/******************************************************************************
filename: game_scene.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of GameScene.
******************************************************************************/
#pragma once

struct GameScene : public Scene<GameScene>
{
	GameScene(GameStateManager& gsm)
		: Scene{ gsm }
	{
	}

	void Load() noexcept
	{
		mManager = std::make_unique<Scene::Manager>();

		RegisterComponents();
		RegisterEvents();
		RegisterSystems();

		PlayerLogic::mGSMPtr = &(mGSM.get());
	}

	void Unload() noexcept
	{
		Release();

		Service<AudioManager>::Get().StopAllChannels();
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
			OnMouseMove,
			PlaySound
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
				ZombieAttackLogic,
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
				OnPlaySound,
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