#include "const.h"
#include <JsonParser.h>
#include <PID_v1.h>
#include <TaskScheduler.h>

#ifndef _RAM_H_
#define _RAM_H_

struct debugStruct {
    void mcu(String str) {
        UART.println(String(millis()) + " [MCU] " + String(str));
    }
    void pid(String str) {
        UART.println(String(millis()) + " [PID] " + String(str));
    }
};

debugStruct de;

//------------------------------------------------------
struct uartStruct {
    char uartBuf[UART_MAX];
    volatile byte uartPtr;

    void clear() {
        uartPtr = 0;
        memset(uartBuf, 0, sizeof(uartBuf));
    }

    void run() {
        if(UART.available()) {
            uartBuf[uartPtr] = (char)UART.read();
            if(uartPtr > 0 && uartBuf[uartPtr] == '\n') {
                jsonControl(uartBuf, uartPtr);
                clear();
            } else {
                uartPtr++;
                if(uartPtr >= UART_MAX) {
                    debugln("[UART] full");
                }
            }
        }
    }
};

uartStruct uart;

//------------------------------------------------------
Scheduler ts;
Task t1(500, TASK_ONCE, &Callback1, &ts, true);

//------------------------------------------------------

class MotorClass {
public:
    // general
    byte P_FWD, P_BWD, P_A, P_B, mode;

    // pid
    double input = 0, output = 0, setPoint = 0;
    double kp = 0, ki = 0, kd = 0;
    PID pid;

    MotorClass(double _input, double _output, double _setPoint, double _kp,
               double _ki, double _kd, byte _P_FWD, byte _P_BWD, byte _P_A,
               byte _P_B);
    void run();
};

MotorClass slider(0, 0, 0, 800, 1000, 50, D5, D6, D7, D8);

#endif