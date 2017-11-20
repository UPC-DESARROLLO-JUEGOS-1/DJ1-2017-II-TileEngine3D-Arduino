#include "GameScene.h"
#include <FrameworkUPC\GameFramework.h>

void GameScene::Initialize()
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NCameraManagment* cManagement = framework->GetCameraManagement();
	framework->GetGraphicDevice()->ChangeTo2D();
	
	mQuad = new Quad();
	mQuad->Initialize(10, 10, 80, 80);
	mQuad->SetRenderCamera(cManagement->GetCurrentCamera());

	mArduinoSerial = new ArduinoSerial();
	mArduinoSerial->Initialize(3);
	mArduinoSerial->SetJoystickEventCallback(
		std::bind(&GameScene::OnJoystickEvent, this, std::placeholders::_1));
}

void GameScene::OnJoystickEvent(dtArduinoJoystick data) {
	if (mQuad != nullptr) {
		float x = mQuad->GetPosition().x;
		float y = mQuad->GetPosition().y;
		
		x += data.X;
		y += data.Y;

		mQuad->SetX(x);
		mQuad->SetY(y);
	}
}

void GameScene::OnKeyDown(SDL_Keycode key)
{

}

void GameScene::OnKeyUp(SDL_Keycode key)
{

}

void GameScene::Update(float dt)
{
	mQuad->Update(dt);
}

void GameScene::Draw(float dt)
{
	mQuad->Draw(dt);
}
