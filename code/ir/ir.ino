#include <Wire.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "SL5_Bqv9HskOcnwT0oPrGFAyVn0KCofa";
char ssid[] = "KELGHADI"; // isi nama network
char pass[] = "Vitri1972" ; // isi pass wifi, kalau open network isi ""

#define in 14
#define out 12

int count = 0;
int incount = 0;
int outcount = 0;
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
}
void loop()
{
  Blynk.run();
  int in_value = digitalRead(in);
  int out_value = digitalRead(out);
  if (in_value == LOW)
  {
    count++;
    incount++;
    Serial.println("jumlah orang masuk:");
    Serial.println(incount);
    Serial.println("jumlah orang sekarang:");
    Serial.println(count);
    delay(500);
  }

  if (out_value == LOW)
  {
    count--;
    outcount++;
    Serial.println("jumlah orang keluar:");
    Serial.println(outcount);
    Serial.println("jumlah orang sekarang:");
    Serial.println(count);
    delay(500);
  }


  if (count == 0)
  {
    Serial.println("tidak ada orang");
    delay(200);
  }

  Blynk.virtualWrite(V1, incount); // Visitors In
  Blynk.virtualWrite(V2, outcount); // Visitors Out
  Blynk.virtualWrite(V3, count); // Current Visitors
  delay(200);
}
