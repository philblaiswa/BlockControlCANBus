enum ButtonState
{
  UNDEFINED = -1,
  OFF = 0,
  CONTROLLER_1 = 1,
  CONTROLLER_2 = 2,
  CONTROLLER_3 = 3,
};

#define BUTTON_1_PIN 6
#define BUTTON_2_PIN 7
#define BUTTON_3_PIN 8

#define LED_0_PIN A0
#define LED_1_PIN A1
#define LED_2_PIN A2
#define LED_3_PIN A3

ButtonState lastState = ButtonState::UNDEFINED;

void setup() {
  Serial.begin(9600);
  Serial.println("Block Control Server");

  Serial.println("  Initializing buttons as digital input with internal 10k pullups");
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);

  Serial.println("  Initializing LEDs as digital outputs");
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
}

void allLedOff();

void loop() {
  // Rotary button has 3 possible states
  // - OFF
  // - position 1, 2 or 3
  int b1State = digitalRead(BUTTON_1_PIN);
  int b2State = digitalRead(BUTTON_2_PIN);
  int b3State = digitalRead(BUTTON_3_PIN);

  ButtonState newState = lastState;
  if (b1State == 0 && lastState != ButtonState::CONTROLLER_1)
  {
    newState = ButtonState::CONTROLLER_1;
    allLedOff();
    digitalWrite(LED_1_PIN, HIGH);
  }
  else if (b2State == 0 && lastState != ButtonState::CONTROLLER_2)
  {
    newState = ButtonState::CONTROLLER_2;
    allLedOff();
    digitalWrite(LED_2_PIN, HIGH);
  }
  else if (b3State == 0 && lastState != ButtonState::CONTROLLER_3)
  {
    newState = ButtonState::CONTROLLER_3;
    allLedOff();
    digitalWrite(LED_3_PIN, HIGH);
  }
  else if (b1State == 1 && b2State == 1 && b3State == 1 && lastState != ButtonState::OFF)
  {
    newState = ButtonState::OFF;
    allLedOff();
    digitalWrite(LED_0_PIN, HIGH);
  }

  if (newState != lastState)
  {
    Serial.print("state from: ");
    Serial.print(lastState);
    Serial.print(" to ");
    Serial.println(newState);

    Serial.print("["); 
    Serial.print(b1State); 
    Serial.print(","); 
    Serial.print(b2State); 
    Serial.print(","); 
    Serial.print(b3State); 
    Serial.println("]");

    lastState = newState;

    // Send new state via CAN Bus
  }

  delay(100);
}

void allLedOff()
{
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
}
