#include <Arduino.h>
#include <CAN.h>

// 関数プロトタイプ宣言
int receive(char *buf);

void setup()
{
  Serial.begin(115200); // シリアル通信開始
  while (!Serial)
    ;

  Serial.println("CAN Sender");

  CAN.setPins(26, 27);
  if (!CAN.begin(500E3))
  {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }
}

int nCount = 0;

void loop()
{
  Serial.print("start:");
  Serial.println(nCount);

  char buf[256];
  Serial.println(buf);
  sprintf(buf, "w:%d", nCount);
  CAN.beginPacket(0x12);
  CAN.write((uint8_t *)buf, strlen(buf));
  CAN.endPacket();
  nCount++;

  // 受信処理
  memset(buf, '\0', sizeof(buf)); // バッファをクリア（ヌル文字で）
  int size = receive(buf);
  if (size > 0)
  {
    Serial.println(buf);
  }

  delay(10);
}

// receive関数の定義
int receive(char *buf)
{
  int packetSize = CAN.parsePacket();
  if (packetSize > 0)
  {
    int size = 0;
    while (CAN.available())
    {
      buf[size++] = CAN.read();
    }
    return size;
  }
  return 0;
}
