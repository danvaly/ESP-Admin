/*
ESP-Admin
---------------------
Author: Valentin Ghica
First Commit: Feb 1, 2021
Github URL: https://github.com/danvaly/ESP-Admin

*/

#ifndef ESPAdmin_h
#define ESPAdmin_h

#include <functional>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Arduino.h"
#include "stdlib_noniso.h"
#include "pages/admin.h"
#include "vector.h"


#if defined(ESP8266)
    #define HARDWARE "ESP8266"
    #include "ESP8266WiFi.h"
    #include "ESPAsyncTCP.h"
#elif defined(ESP32)
    #define HARDWARE "ESP32"
    #include "WiFi.h"
    #include "AsyncTCP.h"
#endif

#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "Card.h"
#include "Chart.h"

#include "ESPConnect.h"

// Forward Declaration
class Card;
class Chart;

// ESPAdmin Class
class ESPAdmin{
  private:
    AsyncWebServer* _server = nullptr;
    AsyncWebSocket* _ws = nullptr;

    Vector<Card*> cards;
    Vector<Chart*> charts;
    bool stats_enabled = false;
    bool basic_auth = false;
    const char *username;
    const char *password;

    // Generate layout json
    String generateLayoutJSON(bool only_stats = false);

    // Generate cards/charts update json
    String generateUpdatesJSON(bool toAll = false);

    // Generate cards/charts update json
    String generateSettingsJSON();

    // Generate Component JSON
    const String generateComponentJSON(Card* card, bool change_only = false);
    const String generateComponentJSON(Chart* chart, bool change_only = false);

    // This method is called when a card/chart is added or removed
    void refreshLayout();

    String getID(){
        String id = "";
        #if defined(ESP8266)
            id = String(ESP.getChipId());
        #elif defined(ESP32)
            id = String((uint32_t)ESP.getEfuseMac(), HEX);
        #endif
        id.toUpperCase();
        return id;
    }


  public:

    ESPAdmin(AsyncWebServer* server, bool enable_stats = true);

    // Set Authentication
    void setAuthentication(const char *user, const char *pass);

    // Add Card
    void add(Card *card);
    // Remove Card
    void remove(Card *card);

    // Add Chart
    void add(Chart *card);
    // Remove Chart
    void remove(Chart *card);

    // Notify client side to update values
    void sendUpdates();
  
    ~ESPAdmin();
};

#endif
