#include <DHT.h>
#include <UbidotsMicroESP8266.h>

#define DHTPIN D1
#define DHTTYPE DHT11

char auth[] = "Your Auth Token";
char ssid[] = "Your Wifi";
char pass[] = "Your Password";

DHT dht(DHTPIN,DHTTYPE);
Ubidots client(auth);
unsigned long last = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(20);
  client.wifiConnection(ssid,pass);
}

void loop() {
  if(millis()-last>10000){
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    last = millis();
    client.add("Humidity",hum);
    client.add("Temperature",temp);
    client.sendAll(true);
  }

}
