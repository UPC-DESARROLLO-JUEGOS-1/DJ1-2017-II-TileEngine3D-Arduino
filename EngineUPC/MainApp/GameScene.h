#pragma once

#include <FrameworkUPC\BaseScene.h>
#include <FrameworkUPC\Quad.h>
#include <FrameworkUPC\ArduinoSerial.h>

class GameScene : public BaseScene
{
public:
	GameScene(SceneGraph* sceneGraph) :
		BaseScene::BaseScene(sceneGraph)
	{}
	~GameScene()
	{
		
	}

	void Initialize();
	void Update(float dt);
	void Draw(float dt);

	void OnJoystickEvent(dtArduinoJoystick data);
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);

private:
	ArduinoSerial* mArduinoSerial;
	Quad* mQuad;
};