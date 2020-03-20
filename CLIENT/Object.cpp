#include "Object.h"
#include <GameWindow.h>

//=============ENGINE================//
#include <Resources.h>


//#ifdef X32
//#ifdef DEBUGMODE
//#pragma comment(lib, "..\\_BIN\\X32\\ENGINED32.lib")
//#elif RELEASEMODE
//#pragma comment(lib, "..\\_BIN\\X32\\ENGINER32.lib")
//#endif
//#elif X64
//#ifdef DEBUGMODE
//#pragma comment(lib, "..\\_BIN\\X64\\ENGINED64.lib")
//#elif RELEASEMODE
//#pragma comment(lib, "..\\_BIN\\X64\\ENGINER64.lib")
//#endif
//#endif


Object::Object() : actor(nullptr)//, sprite(nullptr), texture(nullptr)
{
	//this->Init();
}

Object::Object(My_Ptr<Scene> _Scene, const wchar_t* _Name, Vector4 _CntInfo) : actor(nullptr)//, sprite(nullptr), texture(nullptr)
{
	name = _Name;
	scene = _Scene;	
	spriteCountInfo = _CntInfo;

	this->Init();
}

Object::~Object()
{
}

bool Object::Init()
{	
	//확장자를 제거
	std::wstring actorName = scene->GetName() + name;
	size_t offset = actorName.find_last_of(L'.');
	actorName = actorName.substr(0, offset);

	actor = scene->CreateActor(name.c_str());




	return true;
}