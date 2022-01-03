// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
	, mCurrMotion(-1)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		IdxRange range = mMotionRangeMap[mCurrMotion];
		int framesCount = range.end - range.start + 1;
		int outOfFrame = range.end + 1;				
		
		mCurrFrame += mAnimFPS * deltaTime;
		while (mCurrFrame >= outOfFrame)
		{
			if (range.bCyclic)
				mCurrFrame -= framesCount;
			else
				mCurrFrame = outOfFrame - 1;
		}		

		// Set the current texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	mMotionRangeMap.clear();
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
		CategorizeAnimTextures(-1, 0, mAnimTextures.size() - 1);
		SetCurrentMotion(-1);
	}
}

void AnimSpriteComponent::CategorizeAnimTextures(int motion, int beginIdx, int endIdx, bool bCyclic)
{
	SDL_assert(beginIdx >= 0 && beginIdx <= endIdx);
	SDL_assert(endIdx < mAnimTextures.size());

	mMotionRangeMap.emplace(motion, IdxRange(beginIdx, endIdx, bCyclic));
}

void AnimSpriteComponent::SetCurrentMotion(int motion)
{
	SDL_assert(mMotionRangeMap.find(motion) != mMotionRangeMap.end());

	mCurrMotion = motion;
	mCurrFrame = static_cast<float>(mMotionRangeMap[motion].start);
}
