#include <mcp2515.h>

// MCP 2515
struct can_frame canMsg;
MCP2515 mcp2515(10);  // SPI CS Pin 10 

enum ButtonState
{
  UNDEFINED = -1, // Only used on first loop
  CONTROLLER_0 = 0,
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
  Serial.println("====================");
  Serial.println();

  Serial.println("  Initializing buttons as digital input with internal 10k pullups");
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);

  Serial.println("  Initializing LEDs as digital outputs");
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);

  Serial.println("  Setting up MCP2515");
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

  Serial.println();
  Serial.println("  Setup done");
  Serial.println("====================");
  Serial.println();
}

void AllLedOff();

void loop() {
  // TODO Read CAN bus in case a client wants to receive th state
  //      This will happen if a client is powered on AFTER the server is powered ON

  // Rotary button has 3 possible states
  // - OFF:       CONTROLLER_0
  // - Pins high: CONTROLLER_1, CONTROLLER_2 or CONTROLLER_3
  int b1State = digitalRead(BUTTON_1_PIN);
  int b2State = digitalRead(BUTTON_2_PIN);
  int b3State = digitalRead(BUTTON_3_PIN);

  ButtonState newState = lastState;
  if (b1State == 0 && lastState != ButtonState::CONTROLLER_1)
  {
    newState = ButtonState::CONTROLLER_1;
    AllLedOff();
    digitalWrite(LED_1_PIN, HIGH);
  }
  else if (b2State == 0 && lastState != ButtonState::CONTROLLER_2)
  {
    newState = ButtonState::CONTROLLER_2;
    AllLedOff();
    digitalWrite(LED_2_PIN, HIGH);
  }
  else if (b3State == 0 && lastState != ButtonState::CONTROLLER_3)
  {
    newState = ButtonState::CONTROLLER_3;
    AllLedOff();
    digitalWrite(LED_3_PIN, HIGH);
  }
  else if (b1State == 1 && b2State == 1 && b3State == 1 && lastState != ButtonState::CONTROLLER_0)
  {
    newState = ButtonState::CONTROLLER_0;
    AllLedOff();
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

    sendCANMessage(newState);
  }

  delay(100);
}

void AllLedOff()
{
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
}

void sendCANMessage(int state)
{
  canMsg.can_id  = 0x036; //CAN id as 0x036
  canMsg.can_dlc = 8;     //CAN data length as 8
  canMsg.data[0] = state; //State in first byte
  canMsg.data[1] = 0x00;  //Rest all with 0
  canMsg.data[2] = 0x00;            
  canMsg.data[3] = 0x00;
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;

  Serial.print("Sending CAN message with state: ");
  Serial.println(state);
  mcp2515.sendMessage(&canMsg);     //Sends the CAN message
}
