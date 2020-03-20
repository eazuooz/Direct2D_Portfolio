#include "SelectMapUpdater.h"

#include <Camera.h>
#include <SpriteRenderer.h>
#include <Texture.h>
#include <Sprite.h>
#include <SpriteAnimation.h>
#include <RectRenderer.h>

#include <GameWindow.h>

#include "ENUM.h"
#include "BackGround.h"

SelectMapUpdater::SelectMapUpdater()
{
}


SelectMapUpdater::~SelectMapUpdater()
{
}


void SelectMapUpdater::Loading()
{
	Path::CreatePath(L"SelectMapScene", L"Texture\\SelectScene");

	//CAMERA
	My_Ptr<Actor> mainCam = GetScene()->CreateActor(L"SELECTCAM");
	mainCam->GetTransform()->SetPosition({ 0.0f, 0.0f, -5.0f });
	My_Ptr<Camera> camera = mainCam->AddComponent<Camera>(RENDERGROUP::RG_PLAYER);
	camera->SetProjMode(PROJMODE::ORTHOGONAL);
	camera->SetArea(GameWindow::Inst()->GetWindowSize().x / 100.0f, GameWindow::Inst()->GetWindowSize().y / 100.0f);

	BackGround backGround = BackGround(GetScene(), L"screenback.png", { 1,1,0,0 });


}

void SelectMapUpdater::SceneUpdate()
{

}