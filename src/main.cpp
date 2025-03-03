#include <Arduino.h>
#include <CAN.h>

const int8_t DEVICE_ID = 0x01; // スレーブのID
void onreceive(int packetSize)
{
  if (CAN.parsePacket())
  {
    if (packetSize == 0)
      return; // 受信データがない場合は何もしない
    uint8_t command;
    int8_t receive_date1, receive_date2, receive_date3, receive_date4;

    uint8_t senderID = CAN.packetId(); // 送信元のID
    command = CAN.read();
    receive_date1 = CAN.read();
    receive_date2 = CAN.read();
    receive_date3 = CAN.read();
    receive_date4 = CAN.read();

    // 自分宛のデータなら処理
    if (senderID == DEVICE_ID)
    {
      Serial.print("Received from Master, Command: ");
      Serial.println(command, HEX);

      if (command == 0x01)
      {
        // モーター制御
        Serial.print("Motor Control -> l_x: ");
        Serial.print(receive_date1);
        Serial.print(" l_y: ");
        Serial.println(receive_date2);
        Serial.print(" r_x: ");
        Serial.println(receive_date3);
        Serial.print(" r_y: ");
        Serial.println(receive_date4);
      }
      else if (command == 0x02)
      {
        // ボタン制御
        Serial.print("button Control -> circle: ");
        Serial.print(receive_date1);
        Serial.print(" triangle: ");
        Serial.println(receive_date2);
        Serial.print(" square: ");
        Serial.println(receive_date3);
        Serial.print(" cross: ");
        Serial.println(receive_date4);
      }
    }
  }
};
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
  CAN.onReceive(onreceive);
}

void loop()
{
}
