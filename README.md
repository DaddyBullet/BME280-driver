# BME280-driver
This is super lite HAL driver for BME280 combined humidity and pressure sensor

To make this work you need to write your device specific i2c communication layer in BME280.c file according to its datasheet:
https://www.embeddedadventures.com/datasheets/BME280.pdf

Before using measure functions you have to turn on the sensor by setting non 0 oversampling in appropriate register and, the init calibration tables by calling ```BME280initxxxCompensationTable``` function(s) and set not sleep mod.

This code is tested on Nuvoton NANO130SE3BN
