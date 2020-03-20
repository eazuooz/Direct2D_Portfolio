#pragma once
#include "Resources.h"

#include <fmod.hpp>
#include <map>



#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\TPARTY\\X32\\Debug\\fmodL_vc.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\TPARTY\\X32\\Release\\fmod_vc.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\TPARTY\\X64\\Debug\\fmodL_vc.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\TPARTY\\X64\\Release\\fmod_vc.lib")
#endif
#endif

class Sound;
class SoundPlayer : public ControlBlock
{
	friend Sound;

private:
	Sound* soundClip;
	FMOD::Channel* channel;

public:
	void Stop();
};


class Sound : public Resources
{
public:
	static FMOD::System* mainSoundSystem;

	static FMOD_RESULT __stdcall SoundPlayerCallBack(FMOD_CHANNELCONTROL *channelcontrol, 
		FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
		void *commanddata1, void *commanddata2);

	static bool Init();
	static void Update();

	// Stop도 못시킨다.
	static void Play(const wchar_t* _Name);

	// 재생에 
	static void Play(const wchar_t* _PlayerName, const wchar_t* _Name, int _LoopCount = 1);
	static void Stop(const wchar_t* _PlayerName);

	static My_Ptr<SoundPlayer> FindPlayer(const wchar_t* _PlayerName);

	static std::map<std::wstring, My_Ptr<SoundPlayer>> playerMap;

private:
	FMOD::Sound* sound;

public:
	UINT SoundLength()
	{
		UINT value = -1;
		sound->getLength(&value, FMOD_TIMEUNIT_MS);
		return value;
	}

public:
	bool Load();


public:												 
	Sound();									
	~Sound();									
};

