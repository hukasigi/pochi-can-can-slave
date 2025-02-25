#include <Arduino.h>
#include <CAN.h>

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  CAN.setPins(26, 27);

  // CAN バスの初期化（500 kbps）
  if (!CAN.begin(500E3))
  {
    Serial.println("CAN の初期化に失敗しました！");
    while (1)
      ;
  }
  Serial.println("CAN バス初期化完了");
}

void loop()
{
  if (CAN.parsePacket())
  {
    // 受信した CAN ID を表示
    Serial.print("受信パケット ID: 0x");
    Serial.println(CAN.packetId(), HEX);

    // 受信データを表示
    // Serial.print("Data: ");
    while (CAN.available())
    {
      int8_t byteReceived_lx = CAN.read();
      int8_t byteReceived_ly = CAN.read();
      int8_t byteReceived_rx = CAN.read();
      int8_t byteReceived_ry = CAN.read();
      int8_t l_x = (int8_t)byteReceived_lx;
      int8_t l_y = (int8_t)byteReceived_ly;
      int8_t r_x = (int8_t)byteReceived_rx;
      int8_t r_y = (int8_t)byteReceived_ry;
      int16_t date_lx = map(l_x, -127, 127, -255, 255);
      int16_t date_ly = map(l_y, -127, 127, -255, 255);
      int16_t date_rx = map(r_x, -127, 127, -255, 255);
      int16_t date_ry = map(r_y, -127, 127, -255, 255);
      Serial.print("l_x");
      Serial.println(date_lx);
      Serial.print("l_y");
      Serial.println(date_ly);
      Serial.print("r_x");
      Serial.println(date_rx);
      Serial.print("r_y");
      Serial.println(date_ry);
    }
  }
}
