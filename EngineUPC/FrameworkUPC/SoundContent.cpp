#include "SoundContent.h"
#include "FatalError.h"

void SoundContent::Initialize()
{
	BaseContent::Initialize();
}

bool SoundContent::Load(const std::string path)
{
	alGenSources((ALuint)1, &mSoundId);
	AlutError();

	mSoundBuffer = alutCreateBufferFromFile(path.c_str());
	AlutError();

	alSourcei(mSoundId, AL_BUFFER, mSoundBuffer);
	AlutError();

	alSourcef(mSoundId, AL_PITCH, 1);
	AlutError();

	alSource3f(mSoundId, AL_POSITION, 0, 0, 0);
	AlutError();

	alSource3f(mSoundId, AL_VELOCITY, 0, 0, 0);
	AlutError();

	return true;
}
