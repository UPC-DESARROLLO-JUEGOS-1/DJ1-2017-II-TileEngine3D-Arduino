#include "Sound.h"
#include "FatalError.h"
#include "GameFramework.h"


void Sound::Initialize(const std::string path)
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ContentManager* contentManager = framework->GetContentManager();

	mContent = contentManager->LoadAndGetContent<SoundContent>(path);
}

void Sound::Play(ALfloat volume)
{
	if (volume > 1)
		volume = 1;

	alSourcef(mContent->getSoundId(), AL_GAIN, volume);
	AlutError();

	alSourcei(mContent->getSoundId(), AL_LOOPING, AL_FALSE);
	AlutError();

	alSourcePlay(mContent->getSoundId());
	AlutError();
}

void Sound::Loop(ALfloat volume)
{
	if (volume > 1)
		volume = 1;
	alSourcef(mContent->getSoundId(), AL_GAIN, volume);
	AlutError();

	alSourcei(mContent->getSoundId(), AL_LOOPING, AL_TRUE);
	AlutError();

	alSourcePlay(mContent->getSoundId());
	AlutError();
}
