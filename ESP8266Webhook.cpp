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

#include "ESP8266Webhook.h"

Webhook::Webhook(String api_key, String event_name) {
  _api_key = api_key;
  _event_name = event_name;
}

/**
 * Read the response from the core esp32 WiFiClient.
 */
void Webhook::readResponse(WiFiClient *client) {
  unsigned long timeout = millis();
  while (client->available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client->stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client->available()) {
    String line = client->readStringUntil('\r');
    Serial.print(line);
  }

  // Serial.printf("\nClosing connection\n\n");
}

String Webhook::urlEncode(String value) {
  String encodedString = "";

  for (unsigned int i = 0; i < value.length(); i++) {
    if (value[i] == ' ') {
      encodedString += '+';
    } else if (isAlphaNumeric(value[i])) {
      encodedString += value[i];
    } else {
      encodedString += '%';
      encodedString += String(value[i], HEX);
    }
  }

  return encodedString;
}

int Webhook::trigger() {
  return Webhook::trigger("", "", "");
}

int Webhook::trigger(String value_1) {
  return Webhook::trigger(value_1, "", "");
}

int Webhook::trigger(String value_1, String value_2) {
  return Webhook::trigger(value_1, value_2, "");
}

int Webhook::trigger(String value_1, String value_2, String value_3) {
#if defined(ESP8266)
  return triggerESP8266(value_1, value_2, value_3);
#elif defined(ESP32)
  return triggerESP32(value_1, value_2, value_3);
#endif
}

#if defined(ESP8266)

/**
 * Call the IFTTT webhook on an ESP8266.
 */
int Webhook::triggerESP8266(String value_1, String value_2, String value_3) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "http://maker.ifttt.com/trigger/" +
                         _event_name + "/with/key/" + _api_key +
                         "?value1=" + urlEncode(value_1) + "&value2=" + urlEncode(value_2) + "&value3=" + urlEncode(value_3));
  int httpCode = http.GET();
  http.end();
  return httpCode;
}

#endif

#if defined(ESP32)

/**
 * Call the IFTTT webhook on an ESP8266.
 */
int Webhook::triggerESP32(String value_1, String value_2, String value_3) {
  WiFiClient client;

  const char *host = "maker.ifttt.com";
  const int httpPort = 80;
  String readRequest = "GET /trigger/" +
                       _event_name + "/with/key/" + _api_key +
                       "?value1=" + urlEncode(value_1) + "&value2=" + urlEncode(value_2) + "&value3=" + urlEncode(value_3) + " HTTP/1.1\r\n" +
                       "Host: " + host + "\r\n" +
                       "Connection: close\r\n\r\n";

  if (!client.connect(host, httpPort)) {
    // TODO: Return the correct response code
    return 500;
  }

  client.print(readRequest);
  readResponse(&client);

  // TODO: Return the correct response code
  return 200;
}

#endif
