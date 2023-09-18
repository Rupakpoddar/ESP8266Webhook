# Development

The **ESP8266Webhook** library supports both ESP8266 and ESP32, automatically! We handle the `#ifdef` stuff for you 🙇

Library code that isn't for your microcontroller doesn't get included into your program. We gotta conserve space!

- [Getting started](#getting-started)
- [Development using Arduino IDE](#development-using-arduino-ide)
- [Development using PlatformIO](#development-using-platformio)
- [Using secrets in development](#using-secrets-in-development)

<br>

---

<br>

<a name="getting-started"/>

## Getting started

To keep code clean, we use [EditorConfig](https://editorconfig.org/), which many IDEs support.

Arduino IDE doesn't support it, but if you'd like to learn more about using Visual Studio Code, please see [this blog post]().

<br>

<a name="development-using-arduino-ide"/>

## Development using Arduino IDE

If you'd like to contribute to this project, and you're using Arduino IDE 2.x, here's how you can run the `IFTTT_Webhook.ino` example sketch.

> 📝 **A few things to note:**
>
> - Arduino IDE requires the name of the `.ino` sketch to be identical to the parent directory.
> - It also requires that included `.cpp` and `.h` files be located in the same directory as the sketch file, and be `#include`d, in order to open those files for editing in Arduino IDE 🤷‍♂️

**Setup for development**

1. Clone this repo.
2. Copy the `examples/IFTTT_Webhook.ino` file to the project root, and rename it to `ESP8266Webhook.ino` _(to match the parent folder)_
3. You should be able to make changes to the sketch and included files, and run/test it in Arduino IDE.
4. ❗️ Before creating a PR _(unless it's a draft PR)_, be sure to copy that new code to the `examples/IFTTT_Webhook.ino` file, and delete the working file in the project root!
   - The correct structure of an Arduino library requires that example sketch are located in `/examples` 🤔

<br>

<a name="development-using-platformio"/>

## Development using PlatformIO

- [ ] _❗️ to-do: Improve this_

1. Clone this repo
2. Open VS Code, and open the project root.
3. Copy the `examples/IFTTT_Webhook.ino` file to the project root _(no need to rename the `.ino` to match the parent folder)_
4. You should be able to make changes to the sketch and included files, and run/test it in PlatformIO.
5. ❗️ Before creating a PR _(unless it's a draft PR)_, be sure to copy that new code to the `examples/IFTTT_Webhook.ino` file, and delete the working file in the project root!
   - The correct structure of an Arduino library requires that example sketch are located in `/examples` 🤔

<br>

<a name="using-secrets-in-development"/>

## Using secrets in development

You don't want to risk accidentally committing your secret API keys and WiFi info to the repo, so it's encouraged to use a 🔒 `secrets.h` file in development.

1. Create a new `secrets.h` file in the project root _(where your dev sketch is located)_, and paste the following:

   ```cpp
   #define SECRET_WIFI_SSID "your value here"
   #define SECRET_WIFI_PASSWORD "your value here"
   #define SECRET_IFTTT_API_KEY "your value here"
   #define SECRET_IFTTT_EVENT_NAME "your value here"
   ```

   Replace `your value here` with your secrets.

2. Include your secrets file into the `.ino` sketch:

   ```cpp
   #include "secrets.h" // TODO: Delete this before submitting a PR!
   ```

3. In your new `.ino` file in the project root, comment out the existing constants, and initialize them from your secrets file:

   ```cpp
    // #define _SSID "ENTER HERE"      // Your WiFi SSID
    // #define _PASSWORD "ENTER HERE"  // Your WiFi Password
    // #define KEY "ENTER HERE"        // Webhooks Key
    // #define EVENT "ENTER HERE"      // Webhooks Event Name

    /**
     * DEV ONLY: Secrets are defined in secrets.h for development, and are .gitignore'd
     *
     * TODO: Delete this before submitting a PR
     */
    #define _SSID SECRET_WIFI_SSID
    #define _PASSWORD SECRET_WIFI_PASSWORD
    #define KEY SECRET_IFTTT_API_KEY
    #define EVENT SECRET_IFTTT_EVENT_NAME
   ```

4. Copy your new, tested code back to the `examples/IFTTT_Webhook.ino` file, and delete the working file in the project root!
5. Delete the secrets include & init code before posting a PR!
