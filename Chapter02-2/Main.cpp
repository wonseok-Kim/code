// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

struct AtExit
{
	~AtExit() 
	{ 		
		_CrtDumpMemoryLeaks(); 
	}
} doAtExit;

int main(int argc, char** argv)
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	

	Game game;
	bool success = game.Initialize();	
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();		

	return 0;
}

