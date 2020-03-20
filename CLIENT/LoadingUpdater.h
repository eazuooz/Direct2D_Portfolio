#pragma once
#include <Scene.h>


class SpriteRenderer;
class LoadingUpdater : public Scene::Updater
{
private:
	My_Ptr<SpriteRenderer> loadingRender;

private:
	void Loading() override;
	//void Update() override;
	
	void SceneUpdate() override;

public:
	LoadingUpdater();
	~LoadingUpdater();
};

