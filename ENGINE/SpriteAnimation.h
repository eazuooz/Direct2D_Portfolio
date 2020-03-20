#pragma once
#include "Component.h"
#include <map>

class EffectSpriteRenderer;
class SpriteRenderer;
class Sprite;
class SpriteAnimation : public Component
{
private:
	class AnimationData
	{
	public:
		UINT spriteIndex;
		float time;

	public:
		AnimationData(UINT _Sprite, float _Time) : spriteIndex(_Sprite), time(_Time)
		{

		}
	};

	class AnimationClip : public ControlBlock, public Name
	{
	public:
		My_Ptr<Sprite> sprite;
		
		std::wstring curAnimationName;
		//애니메이션을 만들기 위한 정보
		bool loop;
		std::vector<AnimationData> frameData;

		UINT curFrame;
		float curTime;

		bool aniEnd;

		

	public:
		UINT GetFrameIndex();
		int GetCurFrame()
		{
			return curFrame;
		}

	public:
		void Init(My_Ptr<Sprite> _Sprite ,UINT _Start, UINT _End, float _BaseTime);
		void Update();
		void Reset();

	public:
		AnimationClip();
		~AnimationClip();		
	};

private:
	SpriteRenderer* spriteRender;
	EffectSpriteRenderer* subSpriteRenderer;

	std::map<std::wstring, My_Ptr<AnimationClip>> animationMap;
	My_Ptr<AnimationClip> curAni;
	My_Ptr<AnimationClip> nextAni;

public:
	void SetEffectSprite(EffectSpriteRenderer* _Sprite)
	{
		subSpriteRenderer = _Sprite;
	}


private:
	My_Ptr<AnimationClip> FindAnimation(const wchar_t* _AniName);



public:
	bool IsAnimationEnd()
	{
		return curAni->aniEnd;
	}

	My_Ptr<AnimationClip> GetCurAni()
	{
		return curAni;
	}

public:
	void Stop();
	void ChangeAnimation(const wchar_t* _AniName);
	bool CreateAnimation( const wchar_t* _AniName, const wchar_t* _SpriteName, UINT _Start, UINT _End, float _Time = 0.1f, bool _Loop = true);

public:
	void Init() override;
	void RenderObjBefore() override;

public:
	SpriteAnimation();
	~SpriteAnimation();
};

