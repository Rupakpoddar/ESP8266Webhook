/*
MIT License

Copyright (c) 2020 Rupak Poddar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <ESP8266Webhook.h>
#include <ESP8266WiFi.h>

#define api_key "Change_this"         //Your Webhook key
#define ifttt_event "Change_this"    //Your IFTTT event name

char ssid[] = "Change_this";       //Your network SSID
char password[] = "Change_this";  //Your network key

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
