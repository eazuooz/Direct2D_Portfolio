#include "LogicHeader.h"
#include <Directory.h>
#include <Input.h>

#include <Resources.h>
#include <Texture.h>
#include <Sprite.h>

void LogicLibrary::Init()
{
	Input::CreateKey(L"LEFT", VK_LEFT);
	Input::CreateKey(L"RIGHT", VK_RIGHT);
	Input::CreateKey(L"UP", VK_UP);
	Input::CreateKey(L"DOWN", VK_DOWN);
	Input::CreateKey(L"ML", VK_LBUTTON);
	Input::CreateKey(L"MR", VK_RBUTTON);


	Directory dic;
	dic.ReplaceToParentPath();
	dic.MoveDirectory(L"_BIN");
	dic.MoveDirectory(L"Texture");

	//Path::root;
	Path::CreatePath(dic.GetFolderName().c_str());
	Path::SetRootDir(dic.GetFullPath());


	std::vector<File> allFolderName;
	dic.GetAllFileName(allFolderName, L"*.*");

	
	//std::wstring temp;
	for (size_t i = 0; i < allFolderName.size(); i++)
	{
		if (i == 0 || i == 1)
		{
			continue;
		}
		//temp = allFolderName[i].GetFullPath();
		
		dic.MoveDirectory(allFolderName[i].GetFileName().c_str());
		Path::CreatePath(allFolderName[i].GetFileName().c_str());

		std::vector<File> allFileName;
		dic.GetAllFileName(allFileName, L"*.*");

		std::wstring name;// = dic.GetFolderName();
		for (size_t j = 0; j < allFileName.size(); j++)
		{
			if (j == 0 || j == 1)
			{
				continue;
			}
			name = allFileName[j].GetFileName();

			size_t folderCheck = 0;
			folderCheck = name.find(L'.');

			if (folderCheck > 100000)
			{
				continue;
			}

			Resources::Load<Texture>(Path::JoinPath(allFolderName[i].GetFileName().c_str() ,name.c_str()));
		}
		dic.ReplaceToParentPath();
	}	

	Resources::Create<Sprite>(L"TILE.png", L"TILE.png", 6,9);
	Resources::Create<Sprite>(L"TILEFLOOR.png", L"TILEFLOOR.png", 32, 2);
	Resources::Create<Sprite>(L"CH.png", L"CH.png", 1, 1);
}