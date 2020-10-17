#include "include.h"
#include <stdio.h>    

extern char paTable[];
extern char paTableLen;

//define buffers for sending and receiving
char txBuffer[4];
char rxBuffer[4];
unsigned int i = 0;

void main (void){
    setup(); //call setup function for Raspberry Pi
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    TI_CC_PowerupResetCCxxxx();               // Reset CCxxxx
    writeRFSettings();                        // Write RF settings to config reg
    TI_CC_SPIWriteBurstReg(TI_CCxxx0_PATABLE, paTable, paTableLen);//Write PATABLE
// Configure ports -- GDO0 to RX packet info from CCxxxx 
    portConfig(); 
    interface();
}
//sends a string of data 

void setup(){ //sets up SPI for Raspberry Pi (REPLACE WITH GPIO/ CREATE PI HEADER FILE & use RFStudio)

TI_CC_CSn_PxOUT |= TI_CC_CSn_PIN;
TI_CC_CSn_PxDIR |= TI_CC_CSn_PIN;         // /CS disable

ME1 |= USPIE0;                            // Enable USART0 SPI mode
UCTL0 = SWRST;                            // Disable USART state machine
UCTL0 |= CHAR + SYNC + MM;                // 8-bit SPI Master **SWRST**
UTCTL0 |= CKPH + SSEL1 + SSEL0 + STC;     // SMCLK, 3-pin mode
UBR00 = 0x02;                             // UCLK/2
UBR10 = 0x00;                             // 0
UMCTL0 = 0x00;                            // No modulation
TI_CC_SPI_USART0_PxSEL |= TI_CC_SPI_USART0_SIMO
                        | TI_CC_SPI_USART0_SOMI
                        | TI_CC_SPI_USART0_UCLK;
                                        // SPI option select
TI_CC_SPI_USART0_PxDIR |= TI_CC_SPI_USART0_SIMO + TI_CC_SPI_USART0_UCLK;
                                        // SPI TX out direction
UCTL0 &= ~SWRST;                          // Initialize USART state machine



}

void portConfig(){//configure ports for Raspberry Pi (REPLACE WITH GPIO)

    TI_CC_GDO0_PxIES |= TI_CC_GDO0_PIN;       // Int on falling edge (end of pkt)
    TI_CC_GDO0_PxIFG &= ~TI_CC_GDO0_PIN;      // Clear flag
    TI_CC_GDO0_PxIE |= TI_CC_GDO0_PIN;        // Enable int on end of packet

    TI_CC_SPIStrobe(TI_CCxxx0_SRX);           // Initialize CCxxxx in RX mode.
                                                // When a pkt is received, it will
                                                // signal on GDO0 and wake CPU

    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts


} 


void send(char[] data){
    //int size = sizeOf(data)       //returns the number of bytes in the array
    txBuffer[0] = 2;                          // Packet length
    txBuffer[1] = 0x01;                       // Packet address
    txBuffer[2] = data;                       //data to be sent (string)
    RFSendPacket(txBuffer, 3);      //expects a transmit buffer a size value in char form
}
//receive function that returns a string 
char[] receive(){
    char *temp; //holds the transmission's CRC value
    temp = RFReceivePacket(rxBuffer,3); //stores data in rxBuffer
    if (temp == 0x80){
        return rxBuffer[2];
    }
    else
        error(1);   //Cyclic Redundancy Check failed
}

//method for displaying errors 
void error(int e){
    if (e == 1){ //Cyclic Redundancy Check failed
        printf("Transmission error")
    }

}
//user interface
void interface(){
    int size = 0;
    char str[20];                           //string used for either sending or receiving data
    char send_receive = '';
    printf("Type S to send or R to receive data \n");
    scanf('%c',&send_receive);
    //process for sending data
    if (send_receive == 'R'){
        str = receive(); 

    }
    else if (send_receive == 'S'){
        printf("Enter data to be sent \n");
        scanf("%[^\n]%*c", str);
        RFSendPacket(str);
    }

}