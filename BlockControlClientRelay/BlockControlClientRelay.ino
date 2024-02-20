  #include <mcp2515.h>

// MCP 2515
struct can_frame canMsg;
MCP2515 mcp2515(10);  // SPI CS Pin 10 

// Relay board control
uint8_t orderedPins[] = { A0, A1, A2, A3, A4, A5, 5, 6 };
void clearAll();
void trigger(uint8_t pinIndex, uint8_t val);


void setup() 
{
  Serial.begin(9600);

  Serial.println("Block Control client");
  Serial.println("====================");
  Serial.println();

  Serial.println("  Setting up relays");
  for (int i = 0; i < 8; i++)
  {
    pinMode(orderedPins[i], OUTPUT);
  }
  clearAll();

  Serial.println("  Setting up MCP2515: 40Kbps/8Hz");
  mcp2515.reset();
  mcp2515.setBitrate(CAN_40KBPS,MCP_8MHZ); //Sets CAN at speed 40KBPS and Clock 8MHz
  mcp2515.setNormalMode();

  Serial.println();
  Serial.println("  Setup done");
  Serial.println("====================");
  Serial.println();
}

uint8_t count = -1;

void loop() 
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    int dialPosition = canMsg.data[0];

    Serial.print("Received CAN message, new state is: ");
    Serial.println(dialPosition);

    clearAll();

    // We need to flip 2 relays at once (double throw)
    uint8_t index = dialPosition * 2;
    trigger(index, LOW);
    trigger(index + 1, LOW);
  }

  /*
  // Relay board test
  uint8_t prevPin = count % 8;
  count++;
  uint8_t pin = count % 8;

  Serial.print("Count is ");
  Serial.println(count);

  trigger(prevPin, HIGH);
  trigger(pin, LOW);
  
  delay(2000);
  */
}

void trigger(uint8_t pinIndex, uint8_t val)
{
  uint8_t pin = orderedPins[pinIndex];

  Serial.print("Switching pin index ");
  Serial.print(pinIndex);
  Serial.print("(");
  Serial.print(pin);
  Serial.print(")");
  Serial.print(" to ");
  Serial.println(val == LOW ? "LOW" : "HIGH");

  digitalWrite(pin, val);
}

void clearAll()
{
  for (int i = 0; i < 8; i++)
  {
    trigger(i, HIGH);
  }
}
