#pragma once

#include "Actor.h"
#include "AnimSpriteComponent.h"

class Character : public Actor
{
public:
	Character(class Game* game);
	~Character() override;

	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);

private:
	enum eMotion {
		Walking, Jumping, Punch
	};
	AnimSpriteComponent* mAsc;
};

