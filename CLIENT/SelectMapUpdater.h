#pragma once
#include <Scene.h>

class SelectMapUpdater : public Scene::Updater
{
private:
	void Loading() override;
	void SceneUpdate() override;

public:
	SelectMapUpdater();
	~SelectMapUpdater();
};

