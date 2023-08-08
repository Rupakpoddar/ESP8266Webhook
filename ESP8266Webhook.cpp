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
  WiFiClient client;
  HTTPClient http;
  String encoded_value_1 = urlEncode(value_1);
  String encoded_value_2 = urlEncode(value_2);
  String encoded_value_3 = urlEncode(value_3);
  http.begin(client, "http://maker.ifttt.com/trigger/" +
                         _event_name + "/with/key/" + _api_key +
                         "?value1=" + encoded_value_1 + "&value2=" + encoded_value_2 + "&value3=" + encoded_value_3);
  int httpCode = http.GET();
  http.end();
  return httpCode;
}

/**
 * Encode a string for URLs.
 */
String Webhook::urlEncode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++)
  {
    c = str.charAt(i);
    if (c == ' ')
    {
      encodedString += '+';
    }
    else if (isalnum(c))
    {
      encodedString += c;
    }
    else
    {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9)
      {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9)
      {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      // encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}
