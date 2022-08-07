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
	using ChannelList = std::vector<FMOD::Channel*>;

	void Initialize() noexcept
	{
		FMOD_RESULT result{};
		
		result = FMOD::System_Create(&mSystem);

		assert(result == FMOD_OK);

		result = mSystem->init(1000, FMOD_INIT_NORMAL, 0);

		assert(result == FMOD_OK);
	}

	void CreateSound(const std::string& soundName, const std::string& fileName, bool loop = false) noexcept
	{
		assert(!mSoundMap.count(soundName));
		
		FMOD_RESULT result{};

		FMOD::Sound* newSound;

		FMOD_MODE mode = FMOD_DEFAULT;

		mode |= loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

		result = mSystem->createSound(fileName.c_str(), mode, 0, &newSound);

		assert(result == FMOD_OK);

		mSoundMap[soundName] = newSound;
	}

	void Update() noexcept
	{
		std::erase_if(mChannels, [](const auto& channel)
			{
				bool playing;

				channel->isPlaying(&playing);
				
				return !playing;
			});
		mSystem->update();
	}

	void SetMasterChannelVolume(float vol)
	{
		if (vol < 0)
		{
			vol = 0;
		}

		FMOD::ChannelGroup* master;
		FMOD_RESULT result = mSystem->getMasterChannelGroup(&master);
		
		assert(result == FMOD_OK);

		master->setVolume(vol);
	}

	void PlaySound(const std::string& soundName, float vol = MASTER_VOLUME) noexcept
	{
		assert(mSoundMap.count(soundName));

		FMOD::Channel* newChannel;

		FMOD_RESULT result{};

		result = mSystem->playSound(mSoundMap[soundName], nullptr, false, &newChannel);

		assert(result == FMOD_OK);

		newChannel->setVolume(vol);

		mChannels.emplace_back(newChannel);
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
		for (auto& channel : mChannels)
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
	ChannelList mChannels{};
};