#ifndef SERIAL_HEADER__
#define SERIAL_HEADER__

/* *************************************
 *  Includes
 * *************************************/

#include <stdint.h>
#include <stddef.h>

/* *************************************
 *  Defines
 * *************************************/

#define SERIAL_DATA_PACKET_SIZE 8
#define ACK_BYTE_STRING "b"
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/* *************************************
 *  Global prototypes
 * *************************************/

void SerialInit(void);
void SerialRead(uint8_t *ptrArray, size_t nBytes);
void SerialWrite(const void* ptrArray, size_t nBytes);

#ifdef SERIAL_INTERFACE
EXTERNC void Serial_printf(const char* str, ...);
#endif // SERIAL_INTERFACE

#endif // SERIAL_HEADER__
