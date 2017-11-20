const int X_pin = 0; // analog pin connected to VRx
const int Y_pin = 1; // analog pin connected to VRy
const int PIN_BUTTON = 8; // digital pin for button
const float NOISE_TOLERANCE = 0.01f;

float analogX = 0;
float analogY = 0;
float inputButton = 0;

float mouseX = 0;
float mouseY = 0;
float thresholdX = 0;
float thresholdY = 0;
float lastMouseX = 0;
float lastMouseY = 0;

// USE: For diff and store last
float mouse_speed = 10;
bool sendData = false;

void setup() {
 Serial.begin(115200);
 pinMode(PIN_BUTTON, INPUT_PULLUP);
 thresholdX = analogRead(X_pin) / 1024.0f;
 thresholdY = analogRead(Y_pin) / 1024.0f;
}

void loop() {
  // read from electronics
  analogX = thresholdX - (analogRead(X_pin) / 1024.0f);
  analogY = thresholdY - (analogRead(Y_pin) / 1024.0f);
  inputButton = digitalRead(PIN_BUTTON) == LOW ? 1.00f : 0.00f;
  
  mouseX = analogX * mouse_speed;
  mouseY = analogY * mouse_speed;
  mouseX = computeNoise(mouseX, lastMouseX, NOISE_TOLERANCE);
  mouseY = computeNoise(mouseY, lastMouseY, NOISE_TOLERANCE);
  sendData = (mouseX == 0.0f && mouseY == 0.0f) ? false : true;
  lastMouseX = mouseX;
  lastMouseY = mouseY;

  //if (sendData) {
    Serial.println("{" + String(mouseX) + "," + String(mouseY) + "," + String(inputButton) + "}");
  //}
}

float computeNoise(float value, float lastValue, float noiseTolerance){
  float result = value;

  if (abs(value - lastValue) <= noiseTolerance) {
    result = lastValue;
  }
  
  // Convert it to Strings (Arduino will change as 2 decimal points as default)
  // This algorithm is for supressing any mechanical problem.
  if (value == lastValue) {
    if ((result <= noiseTolerance && result >= -noiseTolerance) || String(abs(result)) == String(noiseTolerance)) {
      result = 0.0f;
    }
  }
  
  return result;
}
