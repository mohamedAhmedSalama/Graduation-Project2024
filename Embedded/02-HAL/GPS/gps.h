#ifndef GPS_H_
#define GPS_H_
#include "RCC_Interface.h"
#include <stdint.h>
#include "../Stm32_F103C6_Drivers/include/uart.h"

#define MAX_STRING_LENGTH 100


//void GPS_Init(void);
uint8_t MUART_ReceiveStringGPS(uint8_t UART_CHANNEL_NAME, char* receivedString);
void parseGPGGA(const char* gpggaString, char* latitude, char* longitude, char* altitude);
void removeChar(char *str, char c);
void removeCharAtIndex(char *str, int index);
void insertChar(char *str, char c, int index);
void appendString(char *destination, const char *source);
void removeCharsFromIndex(char *str, int startIndex);
void removeChars(char *str, int startIndex, int endIndex);
double convertToDecimal(int degrees, double minutes);
float atof_custom(const char *str);
int atoi_custom(const char *str);
void parse(const char* gpggaString, char* altitude,const char* copy1,const char* copy2,const char* copy3,const char* copy4);
#endif /* GPS_H_ */
