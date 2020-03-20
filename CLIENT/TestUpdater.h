#pragma once
#include <Scene.h>


class TestUpdater : public Scene::Updater
{
private:
	void Loading() override;
	void SceneUpdate() override;

	
	
	void ChangeStart() override;
	void ChangeEnd() override;

public:
	TestUpdater();
	~TestUpdater();
};

