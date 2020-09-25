import spidev


bus = 0
device = 0

spi = spidev.SpiDev()
spi.open(bus, device)

spi.max_speed_hz = 500000
spi.mode = 0

deviceOutput = readbytes(10000)
print(deviceOutput)

close()