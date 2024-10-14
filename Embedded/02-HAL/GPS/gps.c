#include "gps.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const USART_CHANNEL="USART2";
const GSM_UART_CHANNEL="UART2";

//void GPS_Init(void) {
//    // Initialize UART for GSM communication
//	MRCC_voidPreipheralEnable(APB1, USART_CHANNEL);
//    MUART_voidInit(GSM_UART_CHANNEL);
//}

/*
uint8_t MUART_ReceiveStringGPS(uint8_t UART_CHANNEL_NAME, char* receivedString) {
    uint8_t i = 0;
    char receivedChar;

    // Receive characters until a newline character is encountered or maximum string length is reached
    while (i < MAX_STRING_LENGTH - 1) {
        receivedChar = MUART_u8ReceiveByteSynch(UART_CHANNEL_NAME); // Receive a byte

        // Check if received character is newline or carriage return
        if (receivedChar == '\n' || receivedChar == '\r') {
            receivedString[i] = '\0'; // Terminate the string
            if (strstr(receivedString, "$GPGGA") != NULL) {
                return 1; // String reception complete with "$GPGGA" found
            } else {
                i = 0; // Reset index to start over
            }
        } else {
            receivedString[i] = receivedChar; // Store the character in the string
            i++;
        }
    }

    receivedString[MAX_STRING_LENGTH - 1] = '\0'; // Ensure string is terminated even if maximum length is reached
    return 0; // Maximum string length reached without finding "$GPGGA"
}
*/

uint8_t MUART_ReceiveStringGPS(uint8_t UART_CHANNEL_NAME, char* receivedString) {
    uint8_t i = 0;
    char receivedChar;

    // Receive characters until a newline character is encountered or maximum string length is reached
    while (i < MAX_STRING_LENGTH - 1) {
        receivedChar = MUART_u8ReceiveByteSynch(UART_CHANNEL_NAME); // Receive a byte

        // Check if received character is newline or carriage return
        if (receivedChar == '\n' || receivedChar == '\r' ) {
            receivedString[i] = '\0'; // Terminate the string
            if (strstr(receivedString, "GPGGA") != NULL) {
                return 1; // String reception complete with "$GPGGA" found
            } else {
                i = 0; // Reset index to start over
            }
        } else {
            receivedString[i] = receivedChar; // Store the character in the string
            i++;
        }
    }

    receivedString[MAX_STRING_LENGTH - 1] = '\0'; // Ensure string is terminated even if maximum length is reached
    return 0; // Maximum string length reached without finding "$GPGGA"
}




void parseGPGGA(const char* gpggaString, char* latitude, char* longitude, char* altitude) {
    // Copy the input string to avoid modifying the original
    char buffer[MAX_STRING_LENGTH];
    strncpy(buffer, gpggaString, MAX_STRING_LENGTH);

    // Tokenize the string based on the comma delimiter
    char* token = strtok(buffer, ",");
    int count = 0;
    while (token != NULL) {
        // Check if the token corresponds to latitude, longitude, or altitude
        switch (count) {
            case 2:
                removeChar(token, '.');
                insertChar(token, '.', 2);
                strcpy(latitude, token);
                break;
            case 4:
                removeChar(token, '.');
                if(token[0]=='0')
                {
                    removeCharAtIndex(token, 0);
                }
                insertChar(token, '.', 2);
                strcpy(longitude, token);
                break;
            case 9:
                strcpy(altitude, token);
                break;
        }
        token = strtok(NULL, ",");
        count++;
    }
}


void parse(const char* gpggaString, char* altitude ,const char* copy1,const char* copy2,const char* copy3,const char* copy4) {
    // Copy the input string to avoid modifying the original
    char buffer[MAX_STRING_LENGTH];
    strncpy(buffer, gpggaString, MAX_STRING_LENGTH);

    // Tokenize the string based on the comma delimiter
    char* token = strtok(buffer, ",");

    int count = 0;
    while (token != NULL) {
        // Check if the token corresponds to latitude, longitude, or altitude
        switch (count) {
            case 2:
                removeChar(token, '.');
                strcpy(copy1,token);
                removeCharsFromIndex(copy1,2);
                removeCharAtIndex(token, 0);
                removeCharAtIndex(token, 0);
                insertChar(token, '.', 2);
                strcpy(copy2,token);

                break;
            case 4:
            {
                if(token[0]=='0') {
                  removeCharAtIndex(token, 0);
                }
				strcpy(copy3,token);
				removeCharsFromIndex(copy3, 2);
				removeChars(token,0,1);
				strcpy(copy4,token);
                break;
            }
            case 9:
                strcpy(altitude, token);
                break;
        }
        token = strtok(NULL, ",");
        count++;
    }
}


void removeChars(char *str, int startIndex, int endIndex) {
    if (startIndex < 0 || startIndex >= strlen(str) || endIndex < 0 || endIndex >= strlen(str) || startIndex > endIndex) {
        printf("Invalid indices\n");
        return;
    }

    memmove(str + startIndex, str + endIndex + 1, strlen(str) - endIndex); // Shift the rest of the string
    str[strlen(str) - (endIndex - startIndex + 1)] = '\0'; // Null-terminate the string
}




void removeCharsFromIndex(char *str, int startIndex) {
    if (startIndex < 0 || startIndex >= strlen(str)) {
        printf("Invalid index\n");
        return;
    }

    str[startIndex] = '\0'; // Null-terminate the string at the given index
}

void removeChar(char *str, char c) {
    int i, j;
    int len = strlen(str);

    for (i = 0, j = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Null-terminate the new string
}

void removeCharAtIndex(char *str, int index) {
    int len = strlen(str);
    if (index < 0 || index >= len) {
        printf("Invalid index\n");
        return;
    }

    memmove(str + index, str + index + 1, len - index); // Remove the character by shifting the rest of the string
}

void insertChar(char *str, char c, int index) {
    int len = strlen(str);
    if (index < 0 || index > len) {
        printf("Invalid index\n");
        return;
    }

    memmove(str + index + 1, str + index, len - index + 1); // Make room for the new character
    str[index] = c;
}
void appendString(char *destination, const char *source) {
    // Calculate the length of the destination string
    int destLength = strlen(destination);

    // Copy the source string to the end of the destination string
    strcpy(destination + destLength, source);
}
 //Function to convert a string to an integer
int atoi_custom(const char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; ++i)
    {
        result = result * 10 + str[i] - '0';
    }

    return sign * result;
}

float atof_custom(const char *str)
{
    float result = 0.0f;
    float sign = 1.0f;
    int i = 0;
    float fraction = 0.0f;
    float divisor = 1.0f;
    int fractionPart = 0;

    if (str[0] == '-')
    {
        sign = -1.0f;
        i++;
    }

    for (; str[i] != '\0'; ++i)
    {
        if (str[i] == '.')
        {
            fractionPart = 1;
            continue;
        }

        if (!fractionPart)
        {
            result = result * 10.0f + str[i] - '0';
        }
        else
        {
            fraction = fraction * 10.0f + str[i] - '0';
            divisor *= 10.0f;
        }
    }

    result += fraction / divisor;

    return sign * result;
}


double convertToDecimal(int degrees, double minutes) {
    return degrees + minutes / 60.0;
}

