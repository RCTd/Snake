#pragma once

#include "Food.hpp"
#include "Logger.hpp"
#include "Snake.hpp"
#include "Timer.hpp"
#include "ObjectManager.hpp"
#include "WorldObject.hpp"

#include <SDL/SDL_events.h>
#include <vector>

class GameWorld
{
public:
	class EventHandler
	{
	private:
		GameWorld* const world;

	public:
		EventHandler(GameWorld& parent);

		void Update();
	};

	typedef std::vector<Food*> Menu;

private:
	Logger::Handle logger;

#error // commenting out the following line stops
	// segfault from happening, even if the variable
	// is never read OR written.
	SentinelFood* sentinel;

	bool quit;
	Timer foodTimer;
	Menu foods;
	Snake player;

	EventHandler eventHandler;
	ObjectManager objectManager;

public:
	GameWorld();

	void Update();
	void Reset();

	void QuitNotify();
	void KeyNotify(SDLKey sym);

	bool Lost() const;
	bool QuitCalled() const;
};