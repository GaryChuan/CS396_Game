/******************************************************************************
filename: audio_manager.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of AudioManager which is in charge
  of handling all creation/playing/releasing of audio.
******************************************************************************/
#pragma once

class AudioManager
{
public:
	using SoundMap = std::unordered_map<std::string, FMOD::Sound*>;
	using ChannelMap = std::unordered_map<std::size_t, FMOD::Channel*>;

	void Initialize() noexcept
	{
		FMOD_RESULT result{};
		
		result = FMOD::System_Create(&mSystem);

		assert(result == FMOD_OK);

		result = mSystem->init(1000, FMOD_INIT_NORMAL, 0);

		assert(result == FMOD_OK);
	}

	void CreateSound(const std::string& soundName, const std::string& fileName) noexcept
	{
		assert(!mSoundMap.count(soundName));
		
		FMOD_RESULT result{};

		FMOD::Sound* newSound;

		result = mSystem->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &newSound);

		assert(result == FMOD_OK);

		mSoundMap[soundName] = newSound;
	}

	void Update() noexcept
	{
		std::vector<ChannelMap::iterator> stoppedChannels{};

		for (auto it = mChannelMap.begin(), itEnd = mChannelMap.end(); it != itEnd; ++it)
		{
			const auto& [CID, channelPtr] = *it;

			bool playing = false;		

			channelPtr->isPlaying(&playing);

			if (!playing)
			{
				stoppedChannels.push_back(it);
			}
		}

		// Clean up stopped channels
		for (auto& it : stoppedChannels)
		{
			mChannelMap.erase(it);
		}

		mSystem->update();
	}

	void StopChannel(std::size_t CID) noexcept
	{
		assert(mChannelMap.count(CID));

		mChannelMap[CID]->stop();
	}

	void PlaySound(const std::string& soundName) noexcept
	{
		assert(mSoundMap.count(soundName));

		FMOD::Channel* newChannel;

		FMOD_RESULT result{};

		result = mSystem->playSound(mSoundMap[soundName], nullptr, false, &newChannel);

		assert(result == FMOD_OK);

		mChannelMap[0] = newChannel;
	}

	void ReleaseSound(const std::string& soundName) noexcept
	{
		assert(mSoundMap.count(soundName));

		FMOD_RESULT result{};

		result = mSoundMap[soundName]->release();

		assert(result == FMOD_OK);
	}

	void StopAllChannels() noexcept
	{
		for (auto& [CID, channel] : mChannelMap)
		{
			channel->stop();
		}
	}

	void ReleaseAllSounds() noexcept
	{
		for (auto& [soundName, sound] : mSoundMap)
		{
			sound->release();
		}
	}

	~AudioManager() noexcept
	{
		ReleaseAllSounds();

		mSystem->release();
	}

private:
	FMOD::System* mSystem{};
	SoundMap mSoundMap{};
	ChannelMap mChannelMap{};
};