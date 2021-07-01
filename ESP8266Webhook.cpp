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

Webhook::Webhook(String api_key, String event_name){
  _api_key = api_key;
  _event_name = event_name;
}

int Webhook::trigger(){
  return Webhook::trigger("", "", "");
}

int Webhook::trigger(String value_1){
  return Webhook::trigger(value_1, "", "");
}

int Webhook::trigger(String value_1, String value_2){
  return Webhook::trigger(value_1, value_2, "");
}

int Webhook::trigger(String value_1, String value_2, String value_3){
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "http://maker.ifttt.com/trigger/" +
              _event_name+"/with/key/"+_api_key +
              "?value1="+value_1+"&value2="+value_2+"&value3="+value_3);
  int httpCode = http.GET();
  http.end();
  return httpCode;
}
