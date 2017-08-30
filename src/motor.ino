#include "ram.h"
#include "const.h"

Motor::Motor(double _input, double _output, double _setPoint, double _kp, double _ki, double _kd, byte _P_FWD, byte _P_BWD)
    : input(_input), output(_output), setPoint(_setPoint), kp(_kp), ki(_ki), kd(_kd), P_FWD(_P_FWD), P_BWD(_P_BWD), pid(&input, &output, &setPoint, kp, ki, kd, DIRECT) {

    pid.SetMode(MANUAL);
    pid.SetSampleTime(1);
    pid.SetOutputLimits(-65535, 65535);
}

void Motor::pwm() {
//   if (output > 0) {
//     pwmWrite(P_FWD, output);
//     pwmWrite(P_BWD, 0);
//   } else if (output < 0) {
//     pwmWrite(P_FWD, 0);
//     pwmWrite(P_BWD, abs(output));
//   } else {
//     pwmWrite(P_FWD, 0);
//     pwmWrite(P_BWD, 0);
//   }
}

void Motor::printa() { UART.print(ki); }
void Motor::seta(double i) { ki = i; }
