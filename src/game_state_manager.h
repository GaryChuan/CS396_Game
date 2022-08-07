#pragma once

enum struct SceneState
{
	MAIN_MENU,
	GAME
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