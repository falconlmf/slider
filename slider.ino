// #include <ESP8266Ping.h>
// #include <ESP8266TrueRandom.h>
// #include <EEPROM.h>
// #include <ESP8266WiFi.h>
// #include <WebSocketsClient.h>
// #include <WiFiUdp.h>
// #include <SimpleTimer.h>
#include "const.h"
#include "ram.h"

//----------------------------------------------------------------------------------------------------
MotorClass::MotorClass(double _input, double _output, double _setPoint, double _kp, double _ki, double _kd, byte _P_FWD, byte _P_BWD, byte _P_A, byte _P_B)
    : input(_input), output(_output), setPoint(_setPoint), kp(_kp), ki(_ki), kd(_kd), P_FWD(_P_FWD), P_BWD(_P_BWD), P_A(_P_A), P_B(_P_B), pid(&input, &output, &setPoint, kp, ki, kd, DIRECT) {
    pinMode(P_A, INPUT);
    pinMode(P_B, INPUT);
    analogWrite(P_FWD, 0);
    analogWrite(P_BWD, 0);
    analogWriteRange(1000);
    pid.SetMode(AUTOMATIC);
    pid.SetSampleTime(10);
    pid.SetOutputLimits(-1000, 1000);
    attachInterrupt(P_A, sliderISR, CHANGE);
}

void MotorClass::run() {
    pid.Compute();

    if(output == 0 || (abs(input - setPoint)) < 5) {
        analogWrite(P_FWD, 0);
        analogWrite(P_BWD, 0);
    } else if(output > 0) {
        analogWrite(P_FWD, output);
        analogWrite(P_BWD, 0);
    } else {
        analogWrite(P_FWD, 0);
        analogWrite(P_BWD, abs(output));
    }
}

//----------------------------------------------------------------------------------------------------
void sliderISR() {
    if(digitalRead(slider.P_A)) {
        digitalRead(slider.P_B) ? slider.input++ : slider.input--;
    } else {
        digitalRead(slider.P_B) ? slider.input-- : slider.input++;
    }
}

void Callback1() {
    de.pid(String(slider.input) + " " + String(slider.output) + " " + String(slider.setPoint));
    t1.restartDelayed();
}

void jsonControl(char *json, byte jsonLen) {
    JsonParser<32> parser;
    JsonHashTable hashTable = parser.parseHashTable(json);

    if(!hashTable.success()) {
        debugmln("json fail");
    } else {
        debugmln(hashTable.getLong("pos"));
        slider.setPoint = hashTable.getLong("pos");
    }
}

//----------------------------------------------------------------------------------------------------
void setup() {
    Serial.begin(115200);
    Serial.print("\n"); // seperate the rubbish
    Serial.print("\n"); // seperate the rubbish
    de.mcu("SDK:" + String(ESP.getSdkVersion()));
    de.mcu("getBootVersion:" + String(ESP.getBootVersion()));
    de.mcu("getBootMode:" + String(ESP.getBootMode()));
    de.mcu("getCpuFreqMHz:" + String(ESP.getCpuFreqMHz()));
    de.mcu("getFlashChipId:" + String(ESP.getFlashChipId()));
    de.mcu("getFlashChipRealSize:" + String(ESP.getFlashChipRealSize()));
    de.mcu("getFlashChipSize:" + String(ESP.getFlashChipSize()));
    de.mcu("getFlashChipSpeed:" + String(ESP.getFlashChipSpeed()));
    de.mcu("getFlashChipMode:" + String(ESP.getFlashChipMode()));
    de.mcu("getFlashChipSize:" + String(ESP.getFlashChipSize()));
    de.mcu("start");

    ESP.wdtEnable(WDTO_1S);
}

void loop() {
    ESP.wdtFeed();
    ts.execute();
    uart.run();
    slider.run();
}