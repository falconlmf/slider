#define F_DEBUG 1
#define UART				Serial
#define debug( x )			( F_DEBUG? UART.print( x ) 	: UART.print("") )
#define debugln( x )		( F_DEBUG? UART.println( x ) : UART.print("") )
#define debugm( x )			( F_DEBUG? UART.print(String(millis()) + " " + String(x)) : UART.print("") )
#define debugmln( x )		( F_DEBUG? UART.println(String(millis()) + " " + String(x)) : UART.print("") )
#define debugLED( x, y )	( F_DEBUG2? digitalWrite(x, y) : delayMicroseconds(0) )

#define WDT_TIMEOUT			2500	// ms
#define UART_MAX 			254
#define EEPROM_MAX_LENGTH 	70
#define SSID_POSITION 		2
#define LOCALPORT 			7081
#define BROADCASTPORT 		7080
#define WSPORT 				7080
#define WS_RETRY_MAX 		3
#define TCP_CLIENT_MAX		10
#define WSHOST 				"fireplace-wifi-stage.bull-b.com"
#define WSPATH 				"/"
#define PINGHOST 			"www.baidu.com"
#define MYSSID 				"Fireplace WiFi"

#define SW_WIPE		D5
#define LED_RETRY	D6
#define LED_WIFI	D7
#define LED_WS		D8
#define LED_TCP1	D4
#define LED_TCP2	D3
#define LED_TCP3	D2
