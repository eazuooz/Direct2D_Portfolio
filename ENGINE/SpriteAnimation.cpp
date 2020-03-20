#include "SpriteAnimation.h"

#include "EffectSpriteRenderer.h"
#include "SpriteRenderer.h"
#include "Sampler.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Sprite.h"



//#include "HRENDER.h"
//#include "HSMP.h"
//#include "HMESH.h"
//#include "HCB.h"
//#include "HVTXSHADER.h"
//#include "HPIXSHADER.h"
//#include "HESPRITE.h"

SpriteAnimation::SpriteAnimation() : spriteRender(nullptr), subSpriteRenderer(nullptr)
{
}


SpriteAnimation::~SpriteAnimation()
{
}

My_Ptr<SpriteAnimation::AnimationClip> SpriteAnimation::FindAnimation(const wchar_t* _AniName)
{

	animationMap;
	std::map<std::wstring, My_Ptr<AnimationClip>>::iterator Iter = animationMap.find(_AniName);

	if (Iter == animationMap.end())
	{
		return nullptr;
	}

	return Iter->second;
}

void SpriteAnimation::Stop()
{
	curAni = nullptr;
}

void SpriteAnimation::ChangeAnimation(const wchar_t* _AniName)
{
	if (curAni == nullptr)
	{
		curAni = FindAnimation(_AniName);		
	}

	nextAni = FindAnimation(_AniName);
	if (curAni == nextAni)
	{
		curAni->curAnimationName = _AniName;
		return;
	}
	else
	{
		curAni = nextAni;
	}
	
	if (nullptr == curAni)
	{
		BOOM;
	}
	curAni->curAnimationName = _AniName;

	curAni->Reset();
}

bool SpriteAnimation::CreateAnimation( const wchar_t* _AniName, const wchar_t* _SpriteName, UINT _Start, UINT _End, float _Time, bool _Loop )
{
	++_End;
#pragma region DEFCODE
	if (nullptr != FindAnimation(_AniName))
	{
		BOOM;
		return false;
	}
	if (_Start > _End)
	{
		BOOM;
		return false;
	}
	My_Ptr<Sprite> FindSprite = Resources::Find<Sprite>(_SpriteName);
	if (nullptr == FindSprite)
	{
		BOOM;
		return false;
	}

	if (_End > FindSprite->GetVectorSize())
	{
		BOOM;
		return false;
	}
#pragma endregion

	AnimationClip* newAnimation = new AnimationClip();
	
	newAnimation->SetName(_AniName);
	newAnimation->loop = _Loop;
	newAnimation->Init(FindSprite ,_Start, _End, _Time);

	animationMap.insert(std::map<std::wstring, My_Ptr<AnimationClip>>::value_type(_AniName, newAnimation));

	if (1 == animationMap.size())
	{
		ChangeAnimation(_AniName);
	}

	return true;
}

void SpriteAnimation::Init()
{
	//render = GetActor()->GetCom<Render>();
	spriteRender	= GetActor()->GetComponent<SpriteRenderer>();
	subSpriteRenderer = GetActor()->GetComponent<EffectSpriteRenderer>();

	if (nullptr == spriteRender)
	{
		BOOM;
		return;
	}
}

void SpriteAnimation::RenderObjBefore()
{
	// 애니메이션은 
	if (nullptr == curAni)
	{
		return;
	}

	curAni->Update();

	//int a = curAni->GetFrameIndex();
	if (nullptr != spriteRender)
	{
		spriteRender->SetSpriteIndex(curAni->GetFrameIndex());
	}
	if (nullptr != subSpriteRenderer)
	{
		subSpriteRenderer->SetSpriteIndex(curAni->GetFrameIndex());
	}
	
}
