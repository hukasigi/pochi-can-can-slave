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
      int16_t l_x = CAN.read();
      int16_t l_y = CAN.read();
      int16_t r_x = CAN.read();
      int16_t r_y = CAN.read();
      l_x = map(l_x, -127, 127, -255, 255);
      l_y = map(l_y, -127, 127, -255, 255);
      r_x = map(r_x, -127, 127, -255, 255);
      r_y = map(r_y, -127, 127, -255, 255);
      Serial.print("l_x");
      Serial.println(l_x);
      Serial.print("l_y");
      Serial.println(l_y);
      Serial.print("r_x");
      Serial.println(r_x);
      Serial.print("r_y");
      Serial.println(r_y);
    }
  }
}
