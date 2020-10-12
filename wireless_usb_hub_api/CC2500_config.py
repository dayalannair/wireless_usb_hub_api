import spidev # pip install spidev
#Bus is 0 or 1, depending on which SPI bus you've connected to
bus = 0
#Device is the chip select pin. Set to 0 or 1, depending on the connections
device = 1

spi = spidev.SpiDev() #Enable SPI
spi.open(bus, device) #Open connection to a specific bus and device (CS pin)

# Set settings (SPI speed and mode)
spi.max_speed_hz = 500000
spi.mode = 0

#data rate: 500kbaud Mod.:MSK, RX BW: 812kHz, Optimised for sensitivity
spi.writebytes(0x0002,0x06)  # IOCFG0        GDO0Output Pin Configuration 
spi.writebytes(0x0008,0x05)  # PKTCTRL0      Packet Automation Control
spi.writebytes(0x000B,0x0C)  # FSCTRL1       Frequency Synthesizer Control 
spi.writebytes(0x000D,0x5D)  # FREQ2         Frequency Control Word, High Byte 
spi.writebytes(0x000E,0x93)  # FREQ1         Frequency Control Word, Middle Byte 
spi.writebytes(0x000F,0xB1)  # FREQ0         Frequency Control Word, Low Byte 
spi.writebytes(0x0010,0x0E)  # MDMCFG4       Modem Configuration 
spi.writebytes(0x0011,0x3B)  # MDMCFG3       Modem Configuration 
spi.writebytes(0x0012,0x73)  # MDMCFG2       Modem Configuration
spi.writebytes(0x0013,0x42)  # MDMCFG1       Modem Configuration
spi.writebytes(0x0015,0x00)  # DEVIATN       Modem Deviation Setting 
spi.writebytes(0x0018,0x18)  # MCSM0         Main Radio Control State Machine Configuration 
spi.writebytes(0x0019,0x1D)  # FOCCFG        Frequency Offset Compensation Configuration
spi.writebytes(0x001A,0x1C)  # BSCFG         Bit Synchronization Configuration
spi.writebytes(0x001B,0xC7)  # AGCCTRL2      AGC Control
spi.writebytes(0x001D,0xB0)  # AGCCTRL0      AGC Control
spi.writebytes(0x0021,0xB6)  # FREND1        Front End RX Configuration 
spi.writebytes(0x0023,0xEA)  # FSCAL3        Frequency Synthesizer Calibration 
spi.writebytes(0x0025,0x00)  # FSCAL1        Frequency Synthesizer Calibration 
spi.writebytes(0x0026,0x19)  # FSCAL0        Frequency Synthesizer Calibration 
# Close the SPI connection
spi.close()