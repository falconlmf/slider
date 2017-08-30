#ifndef _RAM_H_
#define _RAM_H_

#include "const.h"

class Motor {
public:
	// general
	byte P_FWD, P_BWD;

	// pid
	double input = 0, output = 0, setPoint = 0;
	double kp = 0, ki = 0, kd = 0;
    PID pid;

    Motor(double _input, double _output, double _setPoint, double _kp, double _ki, double _kd, byte _P_FWD, byte _P_BWD);
    void pwm();
    void printa();
    void seta(double i);
};

//------------------------------------------------------
char uartBuf[UART_MAX];
volatile byte uartPtr;

//------------------------------------------------------
Scheduler ts;
Task t1(2000, TASK_ONCE, &Callback1, &ts, false);

Motor slider(0, 0, 0, 800, 1000, 50, D5, D6);

#endif