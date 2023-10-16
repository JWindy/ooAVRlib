EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 61E54FAC
P 2850 2500
F 0 "J1" H 2958 2781 50  0000 C CNN
F 1 "Conn_01x04_Male" H 2958 2690 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 2850 2500 50  0001 C CNN
F 3 "~" H 2850 2500 50  0001 C CNN
	1    2850 2500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 61E551A7
P 4050 2600
F 0 "J2" H 4022 2482 50  0000 R CNN
F 1 "Conn_01x04_Male" H 4022 2573 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 4050 2600 50  0001 C CNN
F 3 "~" H 4050 2600 50  0001 C CNN
	1    4050 2600
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J3
U 1 1 61E55D07
P 3500 3300
F 0 "J3" H 3550 2975 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 3550 3066 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 3500 3300 50  0001 C CNN
F 3 "~" H 3500 3300 50  0001 C CNN
	1    3500 3300
	-1   0    0    1   
$EndComp
Text GLabel 3050 2400 2    50   Input ~ 0
RES
Text GLabel 3700 3200 2    50   Input ~ 0
RES
Text GLabel 3050 2700 2    50   Input ~ 0
GND
Text GLabel 3200 3200 0    50   Input ~ 0
GND
Text GLabel 3850 2500 0    50   Input ~ 0
SCK
Text GLabel 3850 2400 0    50   Input ~ 0
VCC
Text GLabel 3850 2600 0    50   Input ~ 0
MISO
Text GLabel 3850 2700 0    50   Input ~ 0
MOSI
Text GLabel 3200 3300 0    50   Input ~ 0
MOSI
Text GLabel 3700 3400 2    50   Input ~ 0
MISO
Text GLabel 3700 3300 2    50   Input ~ 0
SCK
Text GLabel 3200 3400 0    50   Input ~ 0
VCC
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U1
U 1 1 6223FBDF
P 5650 1500
F 0 "U1" H 5121 1546 50  0000 R CNN
F 1 "ATtiny85-20PU" H 5121 1455 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5650 1500 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 5650 1500 50  0001 C CNN
	1    5650 1500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1-Reset1
U 1 1 622435E4
P 5500 2800
F 0 "SW1-Reset1" H 5500 3085 50  0000 C CNN
F 1 "SW_Push" H 5500 2994 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 5500 3000 50  0001 C CNN
F 3 "~" H 5500 3000 50  0001 C CNN
	1    5500 2800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW2-Power1
U 1 1 62243E35
P 3850 1150
F 0 "SW2-Power1" H 3850 1385 50  0000 C CNN
F 1 "SW_SPST" H 3850 1294 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 3850 1150 50  0001 C CNN
F 3 "~" H 3850 1150 50  0001 C CNN
	1    3850 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6224517E
P 3950 1700
F 0 "R1" H 3880 1654 50  0000 R CNN
F 1 "R" H 3880 1745 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 3880 1700 50  0001 C CNN
F 3 "~" H 3950 1700 50  0001 C CNN
	1    3950 1700
	-1   0    0    1   
$EndComp
Text GLabel 6250 1700 2    50   Input ~ 0
RES
Text GLabel 5650 900  1    50   Input ~ 0
VCC
Text GLabel 5650 2100 3    50   Input ~ 0
GND
Text GLabel 6250 1300 2    50   Input ~ 0
MISO
Text GLabel 6250 1200 2    50   Input ~ 0
MOSI
Text GLabel 6250 1400 2    50   Input ~ 0
SCK
NoConn ~ 3100 1350
NoConn ~ 3100 1450
NoConn ~ 3100 1550
NoConn ~ 2700 1750
Text GLabel 2800 1850 3    50   Input ~ 0
GND
$Comp
L Connector:USB_B_Micro J4
U 1 1 6224CF3F
P 2800 1350
F 0 "J4" H 2857 1817 50  0000 C CNN
F 1 "USB_B_Micro" H 2857 1726 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2950 1300 50  0001 C CNN
F 3 "~" H 2950 1300 50  0001 C CNN
	1    2800 1350
	1    0    0    -1  
$EndComp
Text GLabel 4050 1150 2    50   Input ~ 0
VCC
Text GLabel 3950 1850 3    50   Input ~ 0
GND
Text GLabel 5300 2800 0    50   Input ~ 0
RES
Text GLabel 5700 2800 2    50   Input ~ 0
GND
$Comp
L Device:LED D1
U 1 1 62244ACB
P 3950 1400
F 0 "D1" V 3989 1283 50  0000 R CNN
F 1 "LED" V 3898 1283 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 3950 1400 50  0001 C CNN
F 3 "~" H 3950 1400 50  0001 C CNN
	1    3950 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3950 1250 4050 1250
Wire Wire Line
	4050 1250 4050 1150
$Comp
L pspice:CAP C1
U 1 1 62295351
P 3400 1400
F 0 "C1" V 3715 1400 50  0000 C CNN
F 1 "100 nF" V 3624 1400 50  0000 C CNN
F 2 "Capacitor_THT:C_Axial_L5.1mm_D3.1mm_P7.50mm_Horizontal" H 3400 1400 50  0001 C CNN
F 3 "~" H 3400 1400 50  0001 C CNN
	1    3400 1400
	1    0    0    -1  
$EndComp
Text GLabel 3400 1850 3    50   Input ~ 0
GND
Wire Wire Line
	3100 1150 3400 1150
Connection ~ 3400 1150
Wire Wire Line
	3400 1150 3650 1150
Wire Wire Line
	3400 1650 3400 1850
Wire Wire Line
	2800 1750 2800 1850
NoConn ~ 3050 2500
NoConn ~ 3050 2600
NoConn ~ 6250 1500
NoConn ~ 6250 1600
$EndSCHEMATC
