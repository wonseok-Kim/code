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
		int framesCount;
		int outOfFrame;
		bool bCyclic = true;
		if (mCurrMotion < 0)
		{
			framesCount = mAnimTextures.size();
			outOfFrame = mAnimTextures.size();
		}
		else
		{
			IdxRange range = mMotionRangeMap[mCurrMotion];
			framesCount = range.end - range.start + 1;
			outOfFrame = range.end + 1;
			bCyclic = range.bCyclic;
		}
		
		
		mCurrFrame += mAnimFPS * deltaTime;
		while (bCyclic && mCurrFrame >= outOfFrame)
		{
			mCurrFrame -= framesCount;
		}
		if (!bCyclic && mCurrFrame >= outOfFrame)
		{
			mCurrFrame = outOfFrame - 1;
		}

		// Set the current texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
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
