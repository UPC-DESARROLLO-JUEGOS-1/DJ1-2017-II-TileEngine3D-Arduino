#pragma once
#include <AL/alut.h>
#include "SoundContent.h"

class Sound
{
public:
	Sound(){}
	~Sound(){}

	void Initialize(const std::string path);
	void Play(ALfloat volume);
	void Loop(ALfloat volume);

private:
	SoundContent* mContent;
};

