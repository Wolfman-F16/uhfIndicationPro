# UHF Indication Board Pro
This board and firmware can be used standalone or with the UHF Control Board RP.
The full potential is, of course, unlocked with the UHF Control Board RP.

The board can be communicated with using SPI, UART or I2C (not implemented).

![board with annotations](/pcbIndication/uhf_indication_render_ann.png)

# AVR Fuse Bits
Use your ISP programmer of choice to set the fuse bits of the ATmega8 microcontroller. ATTENTION: the pinout of the board is not standard! Make sure you have a modified ribbon cable or use jumper wires to make the appropriate connections!

    avrdude -c <programmer> -p m8 -Ulfuse:v:0xfe:m -Uhfuse:v:0xd1:m

# Flashing Firmware

    avrdude -c <programmer> -p m8 -Uflash:v:UhfIndicationPro.<version>.hex
