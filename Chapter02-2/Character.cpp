#include <vector>

#include "AnimSpriteComponent.h"
#include "Character.h"

Character::Character(Game* game)
	: Actor(game)
{
	
}

Character::~Character()
{
}

void Character::UpdateActor(float deltaTime)
{
}

void Character::ProcessKeyboard(const uint8_t* state)
{
}
