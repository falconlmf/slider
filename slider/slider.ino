// #include <ESP8266Ping.h>
// #include <ESP8266TrueRandom.h>
// #include <EEPROM.h>
// #include <ESP8266WiFi.h>
// #include <WebSocketsClient.h>
// #include <WiFiUdp.h>
// #include <SimpleTimer.h>
#include <JsonParser.h>
#include <PID_v1.h>
#include "ram.h"
#include "const.h"

//------------------------------------------------------
void setup() {
    pinMode(LED_WIFI, OUTPUT);
    pinMode(LED_RETRY, OUTPUT);
    pinMode(LED_WS, OUTPUT);
    pinMode(LED_TCP1, OUTPUT);
    pinMode(LED_TCP2, OUTPUT);
    pinMode(LED_TCP3, OUTPUT);

    delay(2000);
    Serial.begin(115200);
    sendSerial("\n");                       // seperate the rubbish
    sendSerial("\n");                       // seperate the rubbish
    debugmln("* SDK:" + String(ESP.getSdkVersion()));
    debugmln("* getBootVersion:" + String(ESP.getBootVersion()));
    debugmln("* getBootMode:" + String(ESP.getBootMode()));
    debugmln("* getCpuFreqMHz:" + String(ESP.getCpuFreqMHz()));
    debugmln("* getFlashChipId:" + String(ESP.getFlashChipId()));
    debugmln("* getFlashChipRealSize:" + String(ESP.getFlashChipRealSize()));
    debugmln("* getFlashChipSize:" + String(ESP.getFlashChipSize()));
    debugmln("* getFlashChipSpeed:" + String(ESP.getFlashChipSpeed()));
    debugmln("* getFlashChipMode:" + String(ESP.getFlashChipMode()));
    debugmln("* getFlashChipSize:" + String(ESP.getFlashChipSize()));
    debugmln("* start");
    ESP.wdtEnable(WDTO_1S);
}

//------------------------------------------------------
void loop() {
    serialLoop();
    ESP.wdtFeed();
}

//------------------------------------------------------
void serialLoop() {
    while(UART.available()) {
        // get the new byte:
        uartBuf[uartPtr] = (char)UART.read();
        if(uartPtr > 1 && uartBuf[uartPtr] == '\n') {
            debug("[UART] RX:");
            for(byte i = 0; i <= uartPtr; i++) {
                debug(uartBuf[i]);
            }
            // jsonControl(uartBuf, uartPtr);
        } else {
            uartPtr ++;
            if(uartPtr >= UART_MAX) {
                debugln("[UART] full");
            }
        }
        uartClear();
    }
}

//------------------------------------------------------
void uartClear() {
    uartPtr = 0;
    memset(uartBuf, 0, sizeof(uartBuf));
}

//------------------------------------------------------
void sendSerial(String str) {
    Serial.print(str);
}