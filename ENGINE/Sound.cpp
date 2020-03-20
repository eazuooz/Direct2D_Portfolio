#include "Sound.h"
#include <atlstr.h>

FMOD::System* Sound::mainSoundSystem;
std::map<std::wstring, My_Ptr<SoundPlayer>> Sound::playerMap;
void SoundPlayer::Stop()
{
	if (nullptr == channel)
	{
		BOOM;
	}

	channel->stop();
	channel = nullptr;
}

//void SoundPlayer::Play()
//{
//	if (nullptr == channel)
//	{
//		BOOM;
//	}
//
//	channel->
//	channel = nullptr;
//}

Sound::Sound()
{
}


Sound::~Sound()
{
	if (nullptr != sound)
	{
		sound->release();
	}
}

FMOD_RESULT __stdcall Sound::SoundPlayerCallBack(FMOD_CHANNELCONTROL *channelcontrol,
	FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
	void *commanddata1, void *commanddata2)
{
	switch (controltype)
	{
	case FMOD_CHANNELCONTROL_CHANNEL:

		switch (callbacktype)
		{
		case FMOD_CHANNELCONTROL_CALLBACK_END:
		{
			FMOD::Channel* pPointer = ((FMOD::Channel*)channelcontrol);
			void* pSoundPlayer = nullptr;
			pPointer->getUserData(&pSoundPlayer);
			if (nullptr == pSoundPlayer)
			{
				BOOM;
			}

			//HSoundPlayer* CallPlayer = (HSoundPlayer*)pSoundPlayer;

			//if (true == CallPlayer->IsRental())
			//{
			//	return FMOD_OK;
			//}

			//CallPlayer->ReturnPool();

			return FMOD_OK;
		}
		case FMOD_CHANNELCONTROL_CALLBACK_VIRTUALVOICE:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_SYNCPOINT:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_OCCLUSION:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_MAX:
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_FORCEINT:
			break;
		default:
			break;
		}
		break;
	case FMOD_CHANNELCONTROL_CHANNELGROUP:
		break;
	case FMOD_CHANNELCONTROL_MAX:
		break;
	case FMOD_CHANNELCONTROL_FORCEINT:
		break;
	default:
		break;
	}

	return FMOD_OK;
}

bool Sound::Init()
{
	FMOD_RESULT Return = FMOD::System_Create(&mainSoundSystem);
	if (nullptr == mainSoundSystem || FMOD_OK != Return)
	{
		BOOM;
		return false;
	}

	Return = mainSoundSystem->init(32, FMOD_DEFAULT, nullptr);
	if (FMOD_OK != Return)
	{
		BOOM;
		return false;
	}

	return true;
}
void Sound::Update()
{
	if (nullptr != mainSoundSystem)
	{
		mainSoundSystem->update();
	}
}

void Sound::Play(const wchar_t* _Name)
{
	My_Ptr<Sound> FindSound = Resources::Find<Sound>(_Name);

	if (nullptr == FindSound)
	{
		BOOM;
		return;
	}
	

	Sound::mainSoundSystem->playSound(FindSound->sound, nullptr, false, nullptr);
}

void Sound::Play(const wchar_t* _PlayerName, const wchar_t* _Name, int _LoopCount )
{
	My_Ptr<Sound> FindSound = Resources::Find<Sound>(_Name);

	if (nullptr == FindSound)
	{
		BOOM;
		return;
	}


	if (nullptr != FindPlayer(_PlayerName))
	{
		BOOM;
		return;
	}


	SoundPlayer* NewPlayer = new SoundPlayer();
	Sound::mainSoundSystem->playSound(FindSound->sound, nullptr, false, &NewPlayer->channel);

	if (nullptr == NewPlayer->channel)
	{
		BOOM;
	}

	NewPlayer->channel->setCallback(SoundPlayerCallBack);
	NewPlayer->channel->setUserData(NewPlayer);
	NewPlayer->channel->setMode(FMOD_LOOP_NORMAL /*| FMOD_2D*/);
	NewPlayer->channel->setLoopCount(_LoopCount);

	playerMap.insert(std::map<std::wstring, My_Ptr<SoundPlayer>>::value_type(_PlayerName, NewPlayer));
}
 
void Sound::Stop(const wchar_t* _PlayerName)
{
	My_Ptr<SoundPlayer> FindPlaySound = FindPlayer(_PlayerName);
	//SoundPlayer* FindPlaySound = FindPlayer(_PlayerName);


	if (nullptr == FindPlaySound)
	{
		BOOM;
		return;
	}

	FindPlaySound->Stop();
	playerMap.erase(_PlayerName);
}

My_Ptr<SoundPlayer> Sound::FindPlayer(const wchar_t* _PlayerName)
{
	std::map<std::wstring, My_Ptr<SoundPlayer>>::iterator FindPlayerIter = playerMap.find(_PlayerName);

	if (FindPlayerIter == playerMap.end())
	{
		return nullptr;
	}

	return FindPlayerIter->second;
}

bool Sound::Load()
{
	std::string Str = CW2A(file.GetFullPath(), CP_UTF8).m_psz;
	FMOD_RESULT Return = mainSoundSystem->createSound(Str.c_str(), FMOD_DEFAULT, nullptr, &sound);

	if (FMOD_OK != Return || nullptr == sound)
	{
		BOOM;
	}
	return true;
}
