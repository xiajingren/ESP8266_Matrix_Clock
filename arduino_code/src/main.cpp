#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <LedControl.h>
#include <ESP8266WiFi.h>

#include "Font.h";

// 替换为你的网络凭据
const char *ssid = "1505";
const char *password = "13241178098";

// 定义NTP客户端以获取时间
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 8 * 3600);

// MAX7219矩阵屏控制引脚
#define DIN_PIN 13
#define CLK_PIN 14
#define CS_PIN 12
#define NUM_SCREENS 4

// 初始化MAX7219
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, NUM_SCREENS);

void setLed(int addr, int row, byte b)
{
  for (int col = 0; col < 8; col++)
  {
    lc.setLed(addr, row, col, bitRead(b, col));
  }
}

void displayTime()
{
  int h = timeClient.getHours();
  int m = timeClient.getMinutes();
  int s = timeClient.getSeconds();

  Serial.println(String(h) + ":" + String(m) + ":" + String(s));

  for (int row = 0; row < 8; row++)
  {
    byte h1 = NumberFonts[h / 10][row];
    byte h2 = NumberFonts[h % 10][row];

    byte dot = NumberFonts[10][row];

    byte m1 = NumberFonts[m / 10][row];
    byte m2 = NumberFonts[m % 10][row];

    byte s1 = MinNumberFonts[s / 10][row];
    byte s2 = MinNumberFonts[s % 10][row];

    byte row_data1 = h1 | (h2 >> 5);
    byte row_data2 = (h2 << 3) | (dot >> 2) | (m1 >> 4);
    byte row_data3 = (m2 >> 1);
    byte row_data4 = (s1 >> 1) | (s2 >> 5);

    lc.setRow(0, row, row_data1);
    lc.setRow(1, row, row_data2);
    lc.setRow(2, row, row_data3);
    lc.setRow(3, row, row_data4);

    // setLed(0, row, row_data1);
    // setLed(1, row, row_data2);
    // setLed(2, row, row_data3);
    // setLed(3, row, row_data4);
  }
}

void setup()
{
  Serial.println("start...");

  Serial.begin(115200);

  for (int i = 0; i < NUM_SCREENS; i++)
  {
    lc.shutdown(i, false);  // 取消关闭模式
    lc.setIntensity(i, 15); // 设置亮度
    lc.clearDisplay(i);     // 清除显示
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  timeClient.begin();
}

void loop()
{
  timeClient.update();
  // Serial.println(timeClient.getFormattedTime());
  displayTime();

  delay(1000);
}