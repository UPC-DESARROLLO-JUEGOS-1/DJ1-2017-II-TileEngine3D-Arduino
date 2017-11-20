#include "TB3D_Camera.h"
#include "TB3D_Engine.h"

#include <FrameworkUPC\GameFramework.h>
#include <FrameworkUPC\NCameraManagment.h>

#define PiOver4 3.14159265 / 4.0f

TB3D_Camera::TB3D_Camera(TB3D_Engine* engine)
{
	mEngine = engine;
}


TB3D_Camera::~TB3D_Camera()
{
}

void TB3D_Camera::Initialize() {
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NCameraManagment* cManagement = framework->GetCameraManagement();

	framework->GetGraphicDevice()->ChangeTo3D();
	mRenderCamera = (Camera3D*)cManagement->GetCurrentCamera();
}

void TB3D_Camera::Update(float dt) {
	if (mActor != nullptr) {
		mRenderCamera->SetPosition(
			mOffsetX - mActor->GetX(), 
			mOffsetY,
			mOffsetZ - mActor->GetZ()
		);
	}
	
	mRenderCamera->Update(dt);
}