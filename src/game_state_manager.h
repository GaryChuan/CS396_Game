/******************************************************************************
filename: game_state_manager.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project 
Description:
 This file contains the definition of scene state which determines which 
 scene the game is in.

 It also contains the definition of the GameStateManager which manages
 the game state.
******************************************************************************/
#pragma once

enum struct SceneState
{
	MAIN_MENU,
	GAME,
	RETRY_MENU
};

struct GameStateManager
{
	void SetNextScene(SceneState nextScene) noexcept
	{
		mNextScene = nextScene;
	}

	bool ChangeScene() const noexcept
	{
		return mCurrentScene != mNextScene;
	}

	const SceneState& GetCurrentScene() const noexcept
	{
		return mCurrentScene;
	}

	const SceneState& GetNextScene() const noexcept
	{
		return mNextScene;
	}

	void ChangeToNextScene() noexcept
	{
		mCurrentScene = mNextScene;
	}

private:
	SceneState mCurrentScene{SceneState::MAIN_MENU};
	SceneState mNextScene{SceneState::MAIN_MENU};
};