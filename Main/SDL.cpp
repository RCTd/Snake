#include <SDL/SDL.h>
#include <stdexcept>

#include "Common.hpp"

namespace {
struct SDLInitializer
{
	SDLInitializer()
	{
		if(SDL_Init(SDL_INIT_VIDEO))
			throw std::runtime_error("SDL failed to initialize");
	}

	~SDLInitializer()
	{
		SDL_Quit();
	}
} init;
}
