//libraries to inlcude
#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "CC1100-CC2500.h"

//FIFO commands
#define TXFIFO_BURST        0x7F    //write burst only
#define TXFIFO_SINGLE_BYTE  0x3F    //write single only
#define RXFIFO_BURST        0xFF    //read burst only
#define RXFIFO_SINGLE_BYTE  0xBF    //read single only
#define PATABLE_BURST       0x7E    //power control read/write
#define PATABLE_SINGLE_BYTE 0xFE    //power control read/write

//Raspberry Pi pins and settings
#define SPI_CHAN 0 //this is the MOSI for SPI, pin 19
#define SPI_SPEED 8000000 // SPI Clock Speed, should be 4Mhz clock speed
#define SS_PIN 10 // this is the CS pin, however it needs to be manually altered for desired effects, pin 22
#define GDO2 4 //pin 16

//initializing methods
int setup_gpio(void);
void write_to_register(uint8_t address, uint8_t value);
void burst_write(uint8_t address, uint8_t *data_array, uint8_t length);
uint8_t read_from_register(uint8_t address);
void burst_read(uint8_t address, uint8_t *data_array, uint8_t length);
void command_strobe(uint8_t address);
void initializeCC2500();
void flush_RX_FIFO();
void receive_data();
void transmit_data(uint8_t *data_array);
