#pragma once
#include <Scene.h>

class SelectUpdater : public Scene::Updater
{


private:
	void Loading() override;
	void SceneUpdate() override;

public:
	SelectUpdater();
	~SelectUpdater();
};

