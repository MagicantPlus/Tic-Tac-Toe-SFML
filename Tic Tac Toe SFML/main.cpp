#include <iostream>
#include <cstdlib>
#include "Game.h"

int WinMain() {

	Game game;

	// Game loop
	while (game.running()) 
	{
		// Update
		game.update();

		// Render
		game.render();
	}
	
	return 0;
}