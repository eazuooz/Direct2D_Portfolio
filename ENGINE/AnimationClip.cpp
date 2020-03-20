#include "SpriteAnimation.h"
#include <MyTime.h>

#include "Renderer.h"
#include "Sampler.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Sprite.h"


SpriteAnimation::AnimationClip::AnimationClip() : sprite(nullptr), aniEnd(false)
{

}

SpriteAnimation::AnimationClip::~AnimationClip()
{

}


UINT SpriteAnimation::AnimationClip::GetFrameIndex()
{
	return frameData[curFrame].spriteIndex;
}

void SpriteAnimation::AnimationClip::Init(My_Ptr<Sprite> _Sprite, UINT _Start, UINT _End, float _BaseTime)
{
	sprite = _Sprite;

	for (UINT i = _Start; i < _End; ++i)
	{
		frameData.push_back({i, _BaseTime});
	}
}

void SpriteAnimation::AnimationClip::Update()
{


	curTime -= Time::DeltaTime();
	//aniEnd = false;

	if (0.0f >= curTime)
	{
		++curFrame;

		if (true == loop)
		{
			if (frameData.size() <= curFrame)
			{
				Reset();
			}
		}
		else if (false == loop && (int)frameData.size() <= curFrame)
		{
			curFrame = (int)frameData.size() - 1;
			aniEnd = true;			
		}

		
		curTime = frameData[curFrame].time;
	}
}

void SpriteAnimation::AnimationClip::Reset()
{
	curFrame = 0;
	curTime = frameData[0].time;
	aniEnd = false;
}