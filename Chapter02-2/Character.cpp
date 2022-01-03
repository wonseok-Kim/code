#include <cstdio>
#include <cstdlib>
#include <vector>

#include "AnimSpriteComponent.h"
#include "Character.h"
#include "Game.h"

Character::Character(Game* game)
	: Actor(game)
{
	mAsc = new AnimSpriteComponent(this);

	std::vector<SDL_Texture*> textures{};
	textures.reserve(18);
	for (int i = 1; i <= 18; ++i)
	{
		char buffer[32];
		std::snprintf(buffer, _countof(buffer), "Assets/Character%02d.png", i);
		textures.emplace_back(game->GetTexture(buffer));
	}

	mAsc->SetAnimTextures(textures);
	mAsc->SetAnimFPS(15.f);
	mAsc->CategorizeAnimTextures(Walking, 0, 5);
	mAsc->CategorizeAnimTextures(Jumping, 6, 14, false);
	mAsc->CategorizeAnimTextures(Punch, 15, 17, false);
	mAsc->SetCurrentMotion(Walking);			
}

Character::~Character()
{
}

void Character::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
}

void Character::ProcessKeyboard(const uint8_t* state)
{
	if (state[SDL_SCANCODE_W])
	{
		mAsc->SetCurrentMotion(Walking);
	}
	if (state[SDL_SCANCODE_J])
	{
		mAsc->SetCurrentMotion(Jumping);
	}
	if (state[SDL_SCANCODE_P])
	{
		mAsc->SetCurrentMotion(Punch);
	}
}
