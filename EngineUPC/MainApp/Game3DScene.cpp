#include "Game3DScene.h"
#include <FrameworkUPC\GameFramework.h>
#include <FrameworkUPC\FPSCamera.h>

#include "TB3D_Configuration.h"

#define PI 3.14159265
#define PiOver4 PI / 4.0f

void Game3DScene::Initialize()
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NCameraManagment* cManagement = framework->GetCameraManagement();

	int cWidth = framework->GetScreenWidth();
	int cHeight = framework->GetScreenHeight();
	
	// Creamos la camara
	FPSCamera* camera = cManagement->CreateFPSCamera(cWidth, cHeight, PiOver4, 0.01f, 100.0f);
	camera->SetZ(-5.0f);
	// Seteamos como la actual
	cManagement->SetCurrentCamera(camera);

	// Inicializamos el Cubo
	mCube.Initialize(1, 0, 0, 1, 1, 1);
	mCube.SetZ(1.0f);
	mCube.SetRenderCamera(camera);

	// Inicializamos el Modelo 3D
	mStaticModel.Initialize("Models/", "farmhouse_obj.obj", 0.0f, 0, 0);
	mStaticModel.SetRenderCamera(camera);
	mStaticModel.SetScale(0.05f, 0.05f, 0.05f);
}

void Game3DScene::OnKeyDown(SDL_Keycode key)
{
	
}

void Game3DScene::OnKeyUp(SDL_Keycode key)
{
	
}

void Game3DScene::Update(float dt)
{
	float x = mCube.GetRotation().x;
	x += 0.01f;
	mCube.SetRotationX(x);
	mCube.SetRotationZ(x / 2.0f);

	mCube.Update(dt);

	Vector3 rotation = mStaticModel.GetRotation();
	rotation.x += 0.01f;
	mStaticModel.SetRotationX(rotation.x);
	mStaticModel.SetRotationZ(rotation.x / 2.0f);

	mStaticModel.Update(dt);
}

void Game3DScene::Draw(float dt)
{
	mCube.Draw(dt);
	mStaticModel.Draw(dt);
}
