#include "set_wifi.h"
set_wifi setwifi;

const char conect_wifi0[] = "啟動";
const char conect_wifi1[] = "AT";
const char conect_wifi2[] = "力場";

// bool conect_last()
// {
//   uint8_t count = 0;
//   for(;;){
//     delay(100);
//     count ++;
//     if(WiFi.status() == WL_CONNECTED)
//       return 1;
//     if(count == 100)
//       return 0;
//   }
// }

bool set_wifi::power_on_conect()
{
  int8_t x;
  uint8_t buf = 0;
  uint8_t count = 0;
  WiFi.setAutoReconnect(true);
  for (x = 32; x > 7; x--)
  {
    oled.choose_clr(12, 0, 104, 4);
    oled.chinese(12, x, conect_wifi0, 16, 1, 1);
    oled.str(44, x, conect_wifi1, 16, 1, 1);
    oled.chinese(60, x, conect_wifi2, 16, 1, 0);
    oled.choose_refresh(12, 0, 104, 4);
    yield();
  }
  WiFi.mode(WIFI_STA);
  Serial.println("Conect to WiFi:");
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.psk());
  WiFi.begin();
  x = 92;

  for (;;)
  {
    if (WiFi.SSID().c_str() == "")
      break;
    delay(100);
    count++;
    if (WiFi.status() == WL_CONNECTED)
    {
      buf = 1;
      break;
    }
    if (count == 5)
    {
      count = 0;
      buf++;
      if (buf == 20)
      {
        buf = 0;
        break;
      }
      oled.str(x, 7, ".", 16, 1, 0);
      oled.choose_refresh(92, 0, 32, 4);
      x += 8;
      if (x == 116)
      {
        x = 92;
        oled.choose_clr(92, 0, 32, 4);
      }
    }
  }
  for (x = 32; x > 7; x--)
  {
    oled.choose_clr(12, 0, 104, 4);
    oled.chinese(12, x-24, conect_wifi0, 16, 1, 1);
    oled.str(44, x-24, conect_wifi1, 16, 1, 1);
    oled.chinese(60, x-24, conect_wifi2, 16, 1, 0);
    if (buf){
      oled.str(24, x, "AT", 16, 1, 1);
      oled.chinese(40, x, "力場全开", 16, 1, 0);
      }
    else{
      oled.str(12, x, "AT", 16, 1, 1);
      oled.chinese(28, x, "力場啟動失败", 16, 1, 0);
      }
    oled.choose_refresh(12, 0, 104, 4);
    yield();
  }
  delay(500);
  oled.roll(12, 0, 104, 4, 1, UP, 32);
  return buf;
}
