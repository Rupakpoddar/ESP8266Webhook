#ifndef ESP8266Webhook_h
#define ESP8266Webhook_h

#include "Arduino.h"

class Webhook
{
  public:
    Webhook(String api_key, String event_name);

    int trigger(String value_1, String value_2, String value_3);
    int trigger(String value_1, String value_2);
    int trigger(String value_1);
    int trigger();

  private:
    String _api_key;
    String _event_name;
};

#endif

