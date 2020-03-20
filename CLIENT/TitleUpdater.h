#pragma once
#include <Scene.h>


class SpriteAnimation;
class TitleUpdater : public Scene::Updater
{
private:
	My_Ptr<SpriteAnimation> Anirender1;

private:
	void Loading() override;
	void SceneUpdate() override;

public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	TitleUpdater();
	~TitleUpdater();
};

