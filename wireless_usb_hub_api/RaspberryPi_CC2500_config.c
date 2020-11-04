#include "include.h"

//Initializing GPIO pins on Pi for SPI
int setup_gpio(void)
{
    //Set up wiring Pi
    wiringPiSetup();
    //setting up the SPI interface
    wiringPiSPISetup(SPI_CHAN, SPI_SPEED);
    //Setting up GPIO pin to identify the state of the CC2500
    pinMode(GDO2, INPUT);

    return 0;
}

//2 byte array that contains the address of the register and the data to be written to it
//Then transmits the 1 byte of data via a RF signal
void write_to_register(uint8_t address, uint8_t value)
{
    uint8_t buffer[2] = {address, value};
    wiringPiSPIDataRW(0, buffer, 2);
}

//writes out the contents of an array of desired data to the TX FIFO memory (max of 64 bytes of data)
//then transmits the entire array via a RF signal 
void burst_write(uint8_t address, uint8_t *data_array, uint8_t length)
{
    uint8_t buffer[length + 1];
    buffer[0] = address | (uint8_t)TI_CCxxx0_WRITE_BURST;
    for(uint8_t i = 0; i < length; i++)
    {
        buffer[i + 1] = data_array[i];
    }
    wiringPiSPIDataRW(0, buffer, length + 1);
}

//2 byte array, first locations contains the address of the data we want to read from 
//the second array location remains empty to have the data is loaded into it during the SPI read process
uint8_t read_from_register(uint8_t address)
{
    uint8_t buffer[2] = {address | TI_CCxxx0_READ_SINGLE, 0};
    wiringPiSPIDataRW(0, buffer, 2);
    return buffer[1];
}

//An empty array is loaded into the function and the desired address
//then the contents of the chosen address loads into the array
void burst_read(uint8_t address, uint8_t *data_array, uint8_t length)
{
    uint8_t buffer[length + 1];
    buffer[0] = address | (uint8_t)TI_CCxxx0_READ_BURST;
    wiringPiSPIDataRW(0, buffer, length + 1);
    for(uint8_t i = 0; i < length; i++)
    {
        data_array[i] = buffer[i + 1];
    }
}

//This allows access to the multiple features that the CC2500 is capable of
void command_strobe(uint8_t address)
{
    uint8_t buffer[1] = {address};
    wiringPiSPIDataRW(0, buffer, 1);
}

//This loads in the desired values of all the registers of the CC2500
//Things such as RF frequency can be configured here
void initializeCC2500()
{
    write_to_register(TI_CCxxx0_IOCFG2, 0x06);
    write_to_register(TI_CCxxx0_IOCFG1, 0x2E);
    write_to_register(TI_CCxxx0_IOCFG0, 0x06);
    write_to_register(TI_CCxxx0_FIFOTHR, 0x07);
    write_to_register(TI_CCxxx0_SYNC1, 0xD3);
    write_to_register(TI_CCxxx0_SYNC0, 0x91);
    write_to_register(TI_CCxxx0_PKTLEN, 0xFF);
    write_to_register(TI_CCxxx0_PKTCTRL1, 0x04);
    write_to_register(TI_CCxxx0_PKTCTRL0, 0x05);
    write_to_register(TI_CCxxx0_ADDR, 0x00);
    write_to_register(TI_CCxxx0_CHANNR, 0x00);
    write_to_register(TI_CCxxx0_FSCTRL1, 0x08);
    write_to_register(TI_CCxxx0_FSCTRL0, 0x00);
    //FREQ2 - FREQ0 configures the output RF frequency
    write_to_register(TI_CCxxx0_FREQ2, 0x25);
    write_to_register(TI_CCxxx0_FREQ1, 0x80);
    write_to_register(TI_CCxxx0_FREQ0, 0x00); // hopefully 900Mhz frequency
    write_to_register(TI_CCxxx0_MDMCFG4, 0x86);
    write_to_register(TI_CCxxx0_MDMCFG3, 0x83);
    write_to_register(TI_CCxxx0_MDMCFG2, 0x03);
    write_to_register(TI_CCxxx0_MDMCFG1, 0x22);
    write_to_register(TI_CCxxx0_MDMCFG0, 0xF8);
    write_to_register(TI_CCxxx0_DEVIATN, 0x44);
    write_to_register(TI_CCxxx0_MCSM2, 0x07);
    write_to_register(TI_CCxxx0_MCSM1, 0x30);
    write_to_register(TI_CCxxx0_MCSM0, 0x18);
    write_to_register(TI_CCxxx0_FOCCFG, 0x16);
    write_to_register(TI_CCxxx0_BSCFG, 0x6C);
    write_to_register(TI_CCxxx0_AGCCTRL2, 0x03);
    write_to_register(TI_CCxxx0_AGCCTRL1, 0x40);
    write_to_register(TI_CCxxx0_AGCCTRL0, 0x91);
    write_to_register(TI_CCxxx0_WOREVT1, 0x87);
    write_to_register(TI_CCxxx0_WOREVT0, 0x6B);
    write_to_register(TI_CCxxx0_WORCTRL, 0xF8);
    write_to_register(TI_CCxxx0_FREND1, 0x56);
    write_to_register(TI_CCxxx0_FREND0, 0x10);
    write_to_register(TI_CCxxx0_FSCAL3, 0xA9);
    write_to_register(TI_CCxxx0_FSCAL2, 0x0A);
    write_to_register(TI_CCxxx0_FSCAL1, 0x00);
    write_to_register(TI_CCxxx0_FSCAL0, 0x11);
    write_to_register(TI_CCxxx0_RCCTRL1, 0x41);
    write_to_register(TI_CCxxx0_RCCTRL0, 0x00);
    write_to_register(TI_CCxxx0_FSTEST, 0x59);
    write_to_register(TI_CCxxx0_PTEST, 0x7F);
    write_to_register(TI_CCxxx0_AGCTEST, 0x3F);
    write_to_register(TI_CCxxx0_TEST2, 0x88);
    write_to_register(TI_CCxxx0_TEST1, 0x31);
    write_to_register(TI_CCxxx0_TEST0, 0x0B);
}
