#pragma once
#include "BaseContent.h"
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

class SoundContent :
	public BaseContent
{
public:
	SoundContent(ContentManager* contentManagement) :
		BaseContent(contentManagement) { }
	~SoundContent(){}

	ALuint getSoundId() { return mSoundId; }
	ALuint getSoundBuffer() { return mSoundBuffer; }

	void Initialize();
	bool Load(const std::string path);

private:
	ALuint mSoundId, mSoundBuffer;
};

