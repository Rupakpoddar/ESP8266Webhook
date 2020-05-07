#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ESP8266Webhook.h"

Webhook::Webhook(String api_key, String event_name)
{
  _api_key = api_key;
  _event_name = event_name;
}

int Webhook::trigger()
{
  return Webhook::trigger("", "", "");
}

int Webhook::trigger(String value_1)
{
  return Webhook::trigger(value_1, "", "");
}

int Webhook::trigger(String value_1, String value_2)
{
  return Webhook::trigger(value_1, value_2, "");
}

int Webhook::trigger(String value_1, String value_2, String value_3)
{
  HTTPClient http;
  http.begin("http://maker.ifttt.com/trigger/"+_event_name+"/with/key/"+_api_key+"?value1="+value_1+"&value2="+value_2+"&value3="+value_3);
  int httpCode = http.GET();
  http.end();
  return httpCode;
}

