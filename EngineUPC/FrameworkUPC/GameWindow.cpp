#include "GameWindow.h"
#include "EnumWindowFlags.h"
#include "FatalError.h"

GameWindow::GameWindow()
{
}

GameWindow::~GameWindow()
{
}

int GameWindow::Create(const std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags)
{
	//Create Window
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	Uint32 flags = SDL_WINDOW_OPENGL;
	if (windowFlags & EnumWindowFlags::Invisible) flags |= SDL_WINDOW_HIDDEN;
	if (windowFlags & EnumWindowFlags::Fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (windowFlags & EnumWindowFlags::Borderless) flags |= SDL_WINDOW_BORDERLESS;

	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
	if (window == nullptr) FatalError("Couldn't create SDL window");

	//OpenGL Context
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) FatalError("Couldn't create SDL_GLContext");

	//Init Glew
	GLenum error = glewInit();
	
	if(error!=GLEW_OK) FatalError("Couldn't initialize GLEW");

	std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));
	SDL_GL_SetSwapInterval(1); //VSync ON

	//Get default audio device
	ALCdevice *device = alcOpenDevice(NULL);
	if (!device)
		AlutError();

	//OpenAL Context
	ALCcontext *context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
		AlutError();

	//Init Alut
	int argcp = 0;
	char* argv = "/0";
	alutInit(&argcp, &argv);
	AlutError();

	return 0;
}

void GameWindow::Update(float dt)
{
	ProcessInputs();
}

void GameWindow::Present()
{
	SDL_GL_SwapWindow(window); //Swap Buffers
}

void GameWindow::ProcessInputs()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		if (onInputCallback != nullptr)
		{
			onInputCallback(evnt);
		}
	}
}
