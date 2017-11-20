#include "NGraphicDevice.h"
#include "NCameraManagment.h"
#include "GameFramework.h"

#define PiOver4 3.14159265 / 4.0f

void NGraphicDevice::Initialize(int screenWidth, int screenHeight) {
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	SetClearColor(NColor::Blue);

	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void NGraphicDevice::SetClearColor(NColor clearColor) {
	GLclampf r = (float)clearColor.r / 255.0f;
	GLclampf g = (float)clearColor.g / 255.0f;
	GLclampf b = (float)clearColor.b / 255.0f;
	GLclampf a = (float)clearColor.a / 255.0f;

	glClearColor(r, g, b, a);
}

void NGraphicDevice::ChangeTo2D() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	const std::string cameraName = "camera2D";

	NCameraManagment* cManagement = mFramework->GetCameraManagement();
	BaseCamera* camera = cManagement->GetCamera(cameraName);

	if (camera == nullptr) {
		camera = cManagement->CreateCamera2D(mScreenWidth, mScreenHeight);
		cManagement->SaveCamera(cameraName, camera);
	}

	cManagement->SetCurrentCamera(camera);
}

void NGraphicDevice::ChangeTo3D() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	const std::string cameraName = "camera3D";

	NCameraManagment* cManagement = mFramework->GetCameraManagement();
	BaseCamera* camera = cManagement->GetCamera(cameraName);

	if (camera == nullptr) {
		camera = cManagement->CreateCamera3D(mScreenWidth, mScreenHeight,
			PiOver4, 0.01f, 1000.0f);
		cManagement->SaveCamera(cameraName, camera);
	}

	cManagement->SetCurrentCamera(camera);
}

void NGraphicDevice::Update(float dt) {

}

void NGraphicDevice::Draw(float dt) {
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}