#include "TB3D_GameHud.h"
#include <FrameworkUPC\BaseScene.h>
#include <FrameworkUPC\GameFramework.h>

TB3D_GameHud::TB3D_GameHud(BaseScene* scene)
{
	mScene = scene;
}

void TB3D_GameHud::Initialize() {
	mQuad = new Quad();
	mQuad->Initialize(10, 10, 80, 20);
	mQuad->SetRenderCamera(GameFramework::GET_FRAMEWORK()->GetCameraManagement()->GetCurrentCamera());
}

void TB3D_GameHud::OnKeyDown(SDL_Keycode key) {

}

void TB3D_GameHud::OnKeyUp(SDL_Keycode key) {

}

void TB3D_GameHud::Update(float dt) {
	mQuad->Update(dt);
}

void TB3D_GameHud::Draw(float dt) {
	mQuad->Draw(dt);
}
