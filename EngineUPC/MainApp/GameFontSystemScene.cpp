#include "GameFontSystemScene.h"
#include <FrameworkUPC\GameFramework.h>

#include <FrameworkUPC\FontContent.h>
#include <FrameworkUPC\NBitmapFontParser.h>
#include <FrameworkUPC\NBitmapFontCharset.h>

void GameFontSystemScene::Initialize()
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NCameraManagment* cManagement = framework->GetCameraManagement();

	// Creamos la camara
	Camera2D* camera = cManagement->CreateCamera2D(framework->GetScreenWidth(),
		framework->GetScreenHeight());
	// Seteamos como la actual
	cManagement->SetCurrentCamera(camera);

	mTextfield.Initialize(50, 50, "Fonts/kronika_32.fnt");
	mTextfield.SetText("Aloha soy una prueba, en UPC Bitch!");
	mTextfield.SetRenderCamera(camera);
	mTextfield.SetLetterColor(2, NColor::Red);
	mTextfield.SetLetterColor(3, NColor::Blue);
}

void GameFontSystemScene::OnKeyDown(SDL_Keycode key)
{

}

void GameFontSystemScene::OnKeyUp(SDL_Keycode key)
{

}

void GameFontSystemScene::Update(float dt)
{
	mTextfield.Update(dt);
}

void GameFontSystemScene::Draw(float dt)
{
	mTextfield.Draw(dt);
}
