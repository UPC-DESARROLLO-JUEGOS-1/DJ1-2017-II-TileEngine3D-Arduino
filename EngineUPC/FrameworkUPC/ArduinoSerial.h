#pragma once
#pragma warning(disable:4996)

#include <iostream>

using namespace std;

#include <string>
#include <thread>
#include <functional>
#include <stdlib.h>

#include"SerialPort.h"

struct dtArduinoJoystick {
	float X;
	float Y;
	bool buttonA_isPressed;
	bool HasData;
};

class ArduinoSerial {
public:
	ArduinoSerial() {}
	~ArduinoSerial() {
		if (mSerialPort != nullptr) {
			mOnEvent = nullptr;
			delete mSerialPort;
		}
	}

	SerialPort* GetSerialPort() { return mSerialPort; }
	std::function<void(dtArduinoJoystick)> GetOnEvent() { return mOnEvent; }

	void Initialize(int com_port);
	void SetJoystickEventCallback(std::function<void(dtArduinoJoystick)> onEvent) {
		mOnEvent = onEvent;
	}
	void StartListening();

	bool static IsValidFloat(std::string value, int decimals);
	dtArduinoJoystick static FindValidCommand(std::string serialBuffer);
private:
	
	std::function<void(dtArduinoJoystick)> mOnEvent = nullptr;
	SerialPort* mSerialPort;
	std::thread mThread;
};