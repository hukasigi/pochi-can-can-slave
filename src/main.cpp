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
  // 受信パケットの存在確認
  int packetSize = CAN.parsePacket();
  if (packetSize)
  {
    // 受信した CAN ID を表示
    Serial.print("受信パケット ID: 0x");
    Serial.println(CAN.packetId(), HEX);

    // 受信データを順次表示
    Serial.print("Data: ");
    while (CAN.available())
    {
      int byteReceived = CAN.read();
      Serial.print(byteReceived);
      Serial.print(" ");
    }
    Serial.println();
  }
}
