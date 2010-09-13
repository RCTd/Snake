#include "Event.hpp"
#include "Common.hpp"
#include "Direction.hpp"
#include "Snake.hpp"

namespace Event {

namespace {
Snake* player = NULL;
bool* quit = NULL;
}

static int key_handler(SDLKey sym)
{
	assert(player);

	switch(sym)
	{
		case SDLK_LEFT:
			player->ChangeDirection(Direction::left());
			break;
		case SDLK_RIGHT:
			player->ChangeDirection(Direction::right());
			break;
		case SDLK_UP:
			player->ChangeDirection(Direction::up());
			break;
		case SDLK_DOWN:
			player->ChangeDirection(Direction::down());
			break;

		default:
			return 1;
	}
	return 0;
}
static int quit_handler()
{
	assert(quit);

	*quit = true;
	return 0;
}

int SDLCALL Handler(const SDL_Event* event)
{
	switch(event->type)
	{
		case SDL_KEYDOWN:
			return key_handler(event->key.keysym.sym);

		case SDL_QUIT:
			return quit_handler();

		default:
			return 1;
	}
	return 0;
}
void RegisterPlayer(Snake& _player)
{
	player = &_player;
}
void RegisterQuitter(bool& quitter)
{
	quit = &quitter;
}
}
