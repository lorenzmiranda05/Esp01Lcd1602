#include <Arduino.h>
#include <Utility.h>

void setup()
{
  Serial.begin(921600);
  TelnetStream.begin();
  loadConfigFile();
  setupOTA();

  /* colums - 16, rows - 2, pixels - 5x8, SDA - GPIO0, SCL - GPIO2 */
  lcd.begin(COLUMNS, ROWS, LCD_5x8DOTS, 0, 2);
  lcd.setCursor(0, 0);
  lcd.print(F("ESP-01 LCD 1602"));
  lcd.setCursor(0, 1);
  lcd.print(F("Restarting..."));
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0); /* (column, row) index 0 */
  lcd.print(F("Hello Lorenz!"));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Generating your"));
  lcd.setCursor(0, 1);
  lcd.print(F("random numbers!"));
  delay(2000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(F("Random number:"));
}

void loop()
{
  wifiReconnect();
  if (WiFi.status() == WL_CONNECTED)
  {
    ArduinoOTA.handle();
    if (broadcastDeviceDetails == 0)
    {
      // DO SOMETHING
    }
    else
    {
      serialAndTelnetPrintln("");
      serialAndTelnetPrint("Device Name: ");
      serialAndTelnetPrintln(espName);
      serialAndTelnetPrint("WiFi Connection: ");
      serialAndTelnetPrintln(WiFi.SSID());
      serialAndTelnetPrint("MAC Address: ");
      serialAndTelnetPrintln(WiFi.macAddress());
      serialAndTelnetPrint("IP Address: ");
      serialAndTelnetPrintln(WiFi.localIP());
      serialAndTelnetPrintln("Web Server: OFF");
      delay(5000);
    }
  }
  /* prints dynamic text */
  lcd.setCursor(6, 1);
  lcd.print(random(10, 10000));
  lcd.write(LCD_SPACE_SYMBOL);

  delay(1000);
}