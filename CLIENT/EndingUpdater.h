#pragma once
#include <Scene.h>

class EndingUpdater : public Scene::Updater
{
private:
	float bubbleTime1;
	float bubbleTime2;
	float bubbleTime3;
	float rebubbleTime;

private:
	void Loading() override;
	void SceneUpdate() override;

public:
	EndingUpdater();
	~EndingUpdater();
};

