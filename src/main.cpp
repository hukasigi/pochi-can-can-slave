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
    Serial.print("Data: ");
    while (CAN.available())
    {
      int8_t byteReceived = CAN.read();
      int8_t l_x = (int8_t)byteReceived;
      int16_t date = map(l_x, -127, 127, -255, 255);
      Serial.print(date);
      Serial.print(" ");
    }
    Serial.println();
  }
}
