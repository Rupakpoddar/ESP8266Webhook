#include <ESP8266Webhook.h>
#include <ESP8266WiFi.h>

#define _SSID "ENTER HERE"      // Your WiFi SSID
#define _PASSWORD "ENTER HERE"  // Your WiFi Password
#define KEY "ENTER HERE"        // Webhooks Key
#define EVENT "ENTER HERE"      // Webhooks Event Name

Webhook webhook(KEY, EVENT);    // Create an object.

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);

//================================================================//
//================================================================//

  // Trigger with 3 values.
  webhook.trigger("value1","value2","value3");
  delay(5000);

  // Trigger with 2 values.
  webhook.trigger("ABC","XYZ");
  delay(5000);

  // Trigger with 1 value.
  int Num = 1234;
  webhook.trigger(String(Num));
  delay(5000);

  // Trigger without any value and get response.
  int response = webhook.trigger();
  if(response == 200)
    Serial.println("OK");
  else
    Serial.println("Failed");
}

void loop() {
  // Nothing
}
