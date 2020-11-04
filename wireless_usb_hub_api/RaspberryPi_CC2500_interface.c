#include "include.h"


int main()
{
    setup_gpio();
    initializeCC2500();

    //This is to show proof of concept by outputting the numbers 0-7 at a set frequency of 900 Mhz
    uint8_t data[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    while(1)
    {
        transmit_data(data);
        delay(1000);
    }
}

//The following functions deal with the Recevier of the CC2500:

//Clears the RX FIFO memory location which contains the received RF data
void flush_RX_FIFO()
{
    delay(10);
    command_strobe(TI_CCxxx0_SIDLE);
    delay(10);
    command_strobe(TI_CCxxx0_SFRX);
    delay(10);
}

//Turns the CC2500 into a RF receiver
void receive_data()
{
    int packet_length;
    int state;
    int count = 0;

    command_strobe(TI_CCxxx0_SRX);

    do
    {
        state = digitalRead(GDO2);
        delay(1);
        count ++;

    } 
    while (!state);

    while(state)
    {
        state = digitalRead(GDO2);
        delay(100);
    }

    packet_length = read_from_register(TI_CCxxx0_RXFIFO);

    printf("Packet length: %d", packet_length);

    for (int i = 0; i < packet_length - 1; i++)
    {
        printf(", byte: %d: 0x%02X", i, read_from_register(TI_CCxxx0_RXFIFO));
    }

    printf("\r\n");

    command_strobe(TI_CCxxx0_SIDLE);
    command_strobe(TI_CCxxx0_SFRX);

}

//The following function deals with the Transceiver of the CC2500:

//Turns the CC2500 into a RF transmitter
void transmit_data(uint8_t *data_array)
{
    command_strobe(TI_CCxxx0_SIDLE);
    command_strobe(TI_CCxxx0_SFTX);
    burst_write(TXFIFO_BURST, data_array, sizeof(data_array));
    command_strobe(TI_CCxxx0_STX);
}
