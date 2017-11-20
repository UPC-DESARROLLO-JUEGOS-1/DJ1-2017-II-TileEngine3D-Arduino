#include "FatalError.h"
#include <cstdlib>
#include <iostream>
#include <SDL\SDL.h>
#include <AL\alut.h>

void FatalError(std::string message)
{
	std::cout << message << std::endl;
	std::cout << "Press anything to exit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(100);
}

extern void AlutError()
{
	ALenum error = alutGetError();
	if (error != AL_NO_ERROR)
		FatalError(alutGetErrorString(error));
}