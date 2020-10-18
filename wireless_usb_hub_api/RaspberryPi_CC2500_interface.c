#include "include.h"
#include <stdio.h>    

extern char paTable[]; //used to select PA power control settings
extern char paTableLen;

//define buffers for sending and receiving
char txBuffer[4];
char rxBuffer[4];
unsigned int i = 0;

void main (void){
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT (Watch Dog Timer)
    TI_CC_SPISetup();                         // Initialize SPI port
    TI_CC_PowerupResetCCxxxx();               // Reset CCxxxx
    writeRFSettings();                        // Write RF settings to config reg using CC100-CC2500.c file
    TI_CC_SPIWriteBurstReg(TI_CCxxx0_PATABLE, paTable, paTableLen);//Write PATABLE
    portConfig(); // Configure ports -- GDO0 to RX packet info from CCxxxx 
    interface();
}


void portConfig(){//configure ports for Raspberry Pi (REPLACE WITH GPIO)

//----------------------------set up using WiringPi----------------------------------------
    // TI_CC_GDO0_PxIES |= TI_CC_GDO0_PIN;       // Int on falling edge (end of pkt)
    // TI_CC_GDO0_PxIFG &= ~TI_CC_GDO0_PIN;      // Clear flag
    // TI_CC_GDO0_PxIE |= TI_CC_GDO0_PIN;        // Enable int on end of packet
//-----------------------------------------------------------------------------------------

    TI_CC_SPIStrobe(TI_CCxxx0_SRX);           // Initialize CCxxxx in RX mode. When a pkt is received, it will signal on GDO0 and wake CPU
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
    char len = 2 //length of pckt(data and Addr) size byte stripped away in RX function
    temp = RFReceivePacket(rxBuffer,len); //stores data in rxBuffer
    if (temp == 0x80){
        return rxBuffer[1]; //note the address
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