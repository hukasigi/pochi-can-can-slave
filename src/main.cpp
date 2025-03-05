#include <Arduino.h>
#include <CAN.h>

const int8_t DEVICE_ID = 0x10; // スレーブのID
void onReceive(int packetSize)
{
  if (packetSize == 0)
    return;
  Serial.println(packetSize);

  uint8_t targetID = CAN.read(); // 宛先スレーブID
  uint8_t command = CAN.read();
  int8_t receive_data1 = CAN.read();
  int8_t receive_data2 = CAN.read();
  int8_t receive_data3 = CAN.read();
  int8_t receive_data4 = CAN.read();

  // 自分宛のデータか確認
  if (targetID != DEVICE_ID)
    return;

  Serial.print("Received Command: ");
  Serial.println(command, HEX);

  if (command == 0x01)
  {
    Serial.print("Motor Control -> l_x: ");
    Serial.print(receive_data1);
    Serial.print(" l_y: ");
    Serial.println(receive_data2);
    Serial.print(" r_x: ");
    Serial.println(receive_data3);
    Serial.print(" r_y: ");
    Serial.println(receive_data4);
  }
  else if (command == 0x02)
  {
    Serial.print("Button Control -> circle: ");
    Serial.print(receive_data1);
    Serial.print(" triangle: ");
    Serial.println(receive_data2);
    Serial.print(" square: ");
    Serial.println(receive_data3);
    Serial.print(" cross: ");
    Serial.println(receive_data4);
  }
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  CAN.setPins(26, 27);
  if (!CAN.begin(500E3))
  {
    Serial.println("Failed!");
    while (1)
      ;
  }
  Serial.println("Success!");

  CAN.filter(DEVICE_ID, 0xFF);
  CAN.onReceive(onReceive);
}

void loop()
{
}
