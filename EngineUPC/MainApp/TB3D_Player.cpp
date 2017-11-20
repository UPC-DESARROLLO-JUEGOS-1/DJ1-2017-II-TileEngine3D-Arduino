#include "TB3D_Player.h"

#include "TB3D_Engine.h"

TB3D_Player::TB3D_Player(TB3D_Engine* engine) : TB3D_Actor(engine)
{
	mPlayerControl = new TB3D_PlayerControl(this);
}

TB3D_Player::~TB3D_Player()
{
	delete mPlayerControl;

	TB3D_Actor::~TB3D_Actor();
}

void TB3D_Player::CreateCollision(float size) {
	mCollisionCube = new NPrimitiveCube3D();
	mCollisionCube->Initialize(0, 0, 0, size, size, size);
	mCollisionCube->SetColor(NColor::Blue);
	mCollisionCube->SetRenderCamera((BaseCamera*)mEngine->GetCamera()->GetRenderCamera());
}

void TB3D_Player::Initialize() {
	TB3D_Actor::Initialize();

	mPlayerControl->Initialize();

	this->CreateCollision(2.0);

	mDebugMode = true;
	mOffsetX = -(mEngine->GetTileSize() / 2.0);
	mOffsetZ = -(mEngine->GetTileSize() / 2.0);
}

void TB3D_Player::Update(float dt) {
	TB3D_Actor::Update(dt);

	mPlayerControl->Update(dt);
}

void TB3D_Player::Draw(float dt) {
	TB3D_Actor::Draw(dt);
}