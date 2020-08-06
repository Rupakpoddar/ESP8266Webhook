#include <ESP8266Webhook.h>
#include <ESP8266WiFi.h>

char ssid[] = "Change_this";          //Your network SSID
char password[] = "Change_this";     //Your network key

#define api_key "Change_this"      //Your Webhook key
#define ifttt_event "Change_this" //Your IFTTT event name

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

//Attempt to connect to Wifi network:
  Serial.println("");
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("-");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  Webhook webhook(api_key, ifttt_event);        //Create an object

  webhook.trigger("value1","value2","value3");  //Trigger with 3 values
  webhook.trigger("ABC","XYZ");                 //Trigger with 2 values

  int num = 1234;
  webhook.trigger(String(num));                 //Trigger with 1 value

  int request = webhook.trigger();              //Trigger with 0 values
  if(request == 200){ //If http_code is 200, then print "Triggered successfully"
    Serial.println("Triggered successfully!");
  }
  else{
    Serial.println("Failed");
  }
}

void loop() {
}
