#define BLYNK_PRINT Serial

#ifdef ESP32 // ESP32 libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#else // ESP8266 libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#endif



#define echo1  5//echo 1
#define trig1 4 //Trigger 1
#define echo2 14 //echo 2
#define trig2 12 //Trigger 2

int relay = 16; //

long dis_a = 0, dis_b = 0;
int flag1 = 0, flag2 = 0;

int personin = 0 ;
int personout = 0;
int stat = 0;

int MODE = 0;


char auth[] = "SL5_Bqv9HskOcnwT0oPrGFAyVn0KCofa";
char ssid[] = "KELGHADI"; // isi nama network
char pass[] = "Vitri1972" ; // isi pass wifi, kalau open network isi ""


void ultra_read(int pin_t, int pin_e, long &ultra_time)
{
  long time;
  pinMode(pin_t, OUTPUT);
  pinMode(pin_e, INPUT);
  digitalWrite(pin_t, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_t, HIGH);
  delayMicroseconds(10);
  time = pulseIn (pin_e, HIGH);
  ultra_time =  time / 29 / 2;
}



void setup()
{
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  Blynk.begin(auth, ssid, pass);

}

void loop()
{
  Blynk.run();

  //*************************
  ultra_read(trig1, echo1, dis_a); delay(30);
  ultra_read(trig2, echo2, dis_b); delay(30);
  //*************************

  Serial.print("da:");
  Serial.println(dis_a);
  Serial.print("db:");
  Serial.println(dis_b);

  if (dis_a < 90 && flag1 == 0) {
    flag1 = 1;
    if (flag2 == 0) {
      personin = personin + 1;
    }
    delay(100);
  }

  if (dis_b < 90 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      personout = personout + 1;
    }
    delay(100);
  }


  if (dis_a > 90 && dis_b > 90 && flag1 == 1 && flag2 == 1) {
    flag1 = 0, flag2 = 0;
    delay(500);
  }

  stat = personin - personout;
  Serial.print("jumlah orang masuk: ");
  Serial.println(personin);
  Serial.print("jumlah orang keluar: ");
  Serial.println(personout);
  Serial.print("jumlah orang sekarang: ");
  Serial.println(stat);

  Blynk.virtualWrite(V1, personin); // Visitors In
  Blynk.virtualWrite(V2, personout); // Visitors Out
  Blynk.virtualWrite(V3, stat); // Current Visitors
  

}
