#include "Screen.hpp"

#include "Logger.hpp"

#ifdef MSVC
#pragma warning(push, 0)
#endif

#include <SDL_video.h>

#ifdef MSVC
#pragma warning(pop)
#endif

using namespace std;

static Logger::Handle logger = Logger::RequestHandle("Screen");

Screen::Screen(unsigned long _width, unsigned long _height) :
	width(_width), height(_height), bgColor(0, 0, 0)
{
	screen = SDL_SetVideoMode(width, height, 0, SDL_ANYFORMAT | SDL_SWSURFACE);

	if(screen == NULL)
		logger.Fatal(boost::format("Error creating screen: %1%") % SDL_GetError());
}

Screen::~Screen()
{
	SDL_FreeSurface(screen);
}

SDL_Surface* Screen::GetSurface()
{
	++screen->refcount;
	return screen;
}

Point Screen::GetCenter() const
{
	return Point(width / 2, height / 2);
}

Point Screen::GetBounds() const
{
	return Point(width, height);
}

void Screen::Update()
{
	if(SDL_Flip(screen) != 0)
		logger.Fatal(boost::format("Error updating screen: %1%") % SDL_GetError());
}

void Screen::Clear()
{
	SDL_Rect blank;
	blank.x = blank.y = 0;
	blank.w = width;
	blank.h = height;
	SDL_FillRect(screen, &blank, bgColor.GetRGBMap(screen));
}
