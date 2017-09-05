#define F_DEBUG 		1
#define UART 			Serial
#define arr_len( x )  	( sizeof( x ) / sizeof( *x ) )
#define debug(x) 		(F_DEBUG ? UART.print(x) : UART.print(""))
#define debugln(x) 		(F_DEBUG ? UART.println(x) : UART.print(""))
#define debugm(x)		(F_DEBUG ? UART.print(String(millis()) + " " + String(x)) : UART.print(""))
#define debugmln(x)    	(F_DEBUG ? UART.println(String(millis()) + " " + String(x)) : UART.print(""))
#define debugLED(x, y)	 (F_DEBUG2 ? digitalWrite(x, y) : delayMicroseconds(0))

#define WDT_TIMEOUT 2500 // ms
#define UART_MAX 255

void jsonControl(char *json, byte jsonLen);
void sliderISR();
void Callback1();
void sliderSteadyCB();

#define P_FWD D5
#define P_BWD D6
#define P_A D7
#define P_B D8