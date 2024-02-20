# DC Remote Block Control using high speed CAN Bus

This is a prototype to control DC model trains block using CAN-Bus

Material
- Arduino Nano: [Amazon](https://www.amazon.com/dp/B07G99NNXL?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- Arduino Nano Adapter (optional): [Amazon](https://www.amazon.com/dp/B09C5YHQJK?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- MCP2515 CANBus Module Board: [Amazon](https://www.amazon.com/dp/B0BVH43P9L?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- Relay Module (8 channels): [Amazon](https://www.amazon.com/dp/B09ZQRLD95?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- Rotary Switch: [Amazon](https://www.amazon.com/dp/B071XWB3LB?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- LEDs 3mm with resistors : [Amazon](https://www.amazon.com/dp/B07GBFJ823?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- Diode Holders 3mm: [Amazon](https://www.amazon.com/dp/B09XMQWM7X?ref=ppx_yo2ov_dt_b_product_details&th=1)

CAN Bus Library:
- [Arduino MCP2515 CAN interface library](https://github.com/autowp/arduino-mcp2515)
- [Download](https://github.com/autowp/arduino-mcp2515/archive/master.zip)

Server diagram
![Server diagram](https://github.com/philblaiswa/BlockControlCANBus/blob/main/Documentation/ServerDiagram.jpg?raw=true)

Client diagram

![Client diagram](https://github.com/philblaiswa/BlockControlCANBus/blob/main/Documentation/ClientDiagram.jpg?raw=true)

Based on this tutorial: https://circuitdigest.com/microcontroller-projects/arduino-can-tutorial-interfacing-mcp2515-can-bus-module-with-arduino
