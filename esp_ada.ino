include <WiFi.h>

#include "Adafruit_MQTT.h"

#include "Adafruit_MQTT_Client.h"

#define SSID      " "     //WIFI NETWORK NAME

#define Password    "   "//PASSWORD

#define AIO_SERVER      "io.adafruit.com"

#define AIO_SERVERPORT  1883                  

#define AIO_USERNAME   "  " // ENTER USERNAME

#define AIO_KEY         "  " // ENTER AIO KEY

int ledPin = 19 ;

WiFiClient client;     

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);        

Adafruit_MQTT_Subscribe esp_32_feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/esp_32_feed");

void MQTT_connect();

void setup() {

  Serial.begin(115200);

  delay(10);

pinMode(led_gpio,OUTPUT);

  Serial.println(); Serial.println();

  Serial.print("Connecting to WIFI ");

  WiFi.begin(SSID,Password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println();

 Serial.println("WiFi connected");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&esp_32_feed);

}

uint32_t x=0;

void loop() {

   MQTT_connect();

Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(5000))) {

    if (subscription == &esp_32_feed) {

      Serial.print(F("Got: "));

      Serial.println((char *)esp_32_feed.lastread);

       if (!strcmp((char*) esp_32_feed.lastread, "ON"))

      {

        digitalWrite(led_gpio, HIGH);

      }

      else

      {

        digitalWrite(led_gpio, LOW);

      }

    }

  }

}

void MQTT_connect() {

  int8_t again;

  if (mqtt.connected()) {

    return;

  }

 Serial.print("Connecting to Adafruit IO");

uint8_t retry = 5;

  while ((again = mqtt.connect()) != 0) { 

       Serial.println(mqtt.connectErrorString(again));

       Serial.println("Retrying Adafruit connection in 5 seconds...");

       mqtt.disconnect();

       delay(5000);  

       retry--;

       if (retry == 0) {

         while (1);

       }

  }
  Serial.println("");

  Serial.println("Adafruit IO is Connected!");

}
