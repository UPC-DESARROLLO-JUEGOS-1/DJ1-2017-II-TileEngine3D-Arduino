#pragma once

#include "ArduinoSerial.h"
#include "NCommon.h"
#include "ThreadArduinoExecution.h"

void ArduinoSerial::Initialize(int com_port) {
	// change the name of the port with the port name of your computer
	// must remember that the backslashes are essential so do not remove them
	std::string serialPort = "\\\\.\\COM" + std::to_string(com_port);

	mSerialPort = new SerialPort((char*)serialPort.c_str());

	if (mSerialPort->isConnected()) {
		cout << "ArduinoSerial::Connection made in: COM" + std::to_string(com_port) << endl << endl;
	}
	else {
		cout << "ArduinoSerial::Error in port name: COM" + std::to_string(com_port) << endl << endl;
	}
}

void ArduinoSerial::StartListening() {
	// Creating the Thread
	ThreadArduinoExecution threadInstance;
	mThread = std::thread(&ThreadArduinoExecution::Run, &threadInstance,this);
}

bool ArduinoSerial::IsValidFloat(std::string value, int decimals) {
	const int DEFAULT_SIZE = 2;
	bool isValid = false;
	int stringSize = value.size();

	if (stringSize >= (DEFAULT_SIZE + decimals)) {
		bool isMinus = value[0] == '-';

		if (isMinus && stringSize == (DEFAULT_SIZE + decimals + 1)) {
			isValid = true;
		}
		else if (stringSize == (DEFAULT_SIZE + decimals)) {
			isValid = true;
		}
	}

	return isValid;
}

dtArduinoJoystick ArduinoSerial::FindValidCommand(std::string serialBuffer) {
	int offset = 0;
	int endIndex = 0;
	int startIndex = 0;
	bool keepSearching = true;
	dtArduinoJoystick result;
	result.X = 0;
	result.Y = 0;
	result.HasData = false;

	while (keepSearching) {
		startIndex = serialBuffer.find('{', offset);
		endIndex = serialBuffer.find('}', startIndex);

		if (endIndex != -1 && startIndex != -1) {
			string lastCommand = serialBuffer.substr(startIndex + 1, (endIndex - startIndex) - 1);
			lastCommand = NCommon::ReplaceString(lastCommand, "{", "");
			lastCommand = NCommon::ReplaceString(lastCommand, "}", "");
			int commaIndex = lastCommand.find(',', startIndex);
			int nextCommaIndex = lastCommand.find(',', commaIndex + 1);

			if (commaIndex != -1 && nextCommaIndex != -1 && lastCommand.size() > 7) {
				string joystickX = lastCommand.substr(0, commaIndex);
				string joystickY = lastCommand.substr(commaIndex + 1, 4);
				string button = lastCommand.substr(nextCommaIndex + 1, lastCommand.size() - 1);

				if (ArduinoSerial::IsValidFloat(joystickX, 2) && 
					ArduinoSerial::IsValidFloat(joystickY, 2) &&
					ArduinoSerial::IsValidFloat(button, 2)) {
					result.X = stof(joystickX);
					result.Y = stof(joystickY);
					result.buttonA_isPressed = stof(button) >= 1.0f;
					result.HasData = true;

					keepSearching = false;
				}
			}
		}
		else if (endIndex == -1) {
			keepSearching = false;
		}

		offset = endIndex;
	}

	return result;
}