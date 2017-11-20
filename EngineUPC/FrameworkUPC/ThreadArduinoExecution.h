#pragma once

#include "ArduinoSerial.h"
#include <string>

class ThreadArduinoExecution
{
public:
	ThreadArduinoExecution() {}
	ThreadArduinoExecution(const ThreadArduinoExecution & obj) {}

	void Run(ArduinoSerial* arduino) {
		SerialPort* serialPort = arduino->GetSerialPort();
		char output[MAX_DATA_LENGTH];

		while (serialPort->isConnected()) {
			int bytesRead = serialPort->readSerialPort(output, MAX_DATA_LENGTH);

			if (bytesRead > 0) {
				std::string transformedData(output);
				dtArduinoJoystick output = ArduinoSerial::FindValidCommand(transformedData);

				if (output.HasData && arduino->GetOnEvent() != nullptr) {
					arduino->GetOnEvent()(output);
				}
			}
		}
	}
};