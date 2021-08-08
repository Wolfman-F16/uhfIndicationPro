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
L Connector_Generic:Conn_02x05_Odd_Even J1
U 1 1 5FE0D33F
P 6950 3200
F 0 "J1" H 7000 3617 50  0000 C CNN
F 1 "SMD Conn" H 7000 3526 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x05_P2.54mm_Vertical_SMD" H 6950 3200 50  0001 C CNN
F 3 "~" H 6950 3200 50  0001 C CNN
	1    6950 3200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H101
U 1 1 5FE0D6F5
P 5850 5250
F 0 "H101" H 5950 5296 50  0000 L CNN
F 1 "MountingHole" H 5950 5205 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965" H 5850 5250 50  0001 C CNN
F 3 "~" H 5850 5250 50  0001 C CNN
	1    5850 5250
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H102
U 1 1 5FE0D8A1
P 5850 5500
F 0 "H102" H 5950 5546 50  0000 L CNN
F 1 "MountingHole" H 5950 5455 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965" H 5850 5500 50  0001 C CNN
F 3 "~" H 5850 5500 50  0001 C CNN
	1    5850 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3400 7600 3400
Wire Wire Line
	7250 3300 7600 3300
Wire Wire Line
	7250 3200 7600 3200
Wire Wire Line
	7250 3100 7600 3100
Wire Wire Line
	7250 3000 7600 3000
Wire Wire Line
	6750 3400 6300 3400
Wire Wire Line
	6750 3300 6300 3300
Wire Wire Line
	6750 3200 6300 3200
Wire Wire Line
	6750 3100 6300 3100
Wire Wire Line
	6750 3000 6300 3000
Text Label 6300 3400 0    50   ~ 0
PIN_1
Text Label 6300 3300 0    50   ~ 0
PIN_2
Text Label 6300 3200 0    50   ~ 0
PIN_3
Text Label 6300 3100 0    50   ~ 0
PIN_4
Text Label 6300 3000 0    50   ~ 0
PIN_5
Text Label 7600 3400 2    50   ~ 0
PIN_10
Text Label 7600 3300 2    50   ~ 0
PIN_9
Text Label 7600 3200 2    50   ~ 0
PIN_8
Text Label 7600 3100 2    50   ~ 0
PIN_7
Text Label 7600 3000 2    50   ~ 0
PIN_6
$Comp
L Connector_Generic:Conn_02x05_Counter_Clockwise U1
U 1 1 5FE18941
P 4850 3150
F 0 "U1" H 4900 2725 50  0000 C CNN
F 1 "CL03621A" H 4900 2816 50  0000 C CNN
F 2 "Package_DIP:DIP-10_W10.16mm" H 4850 3150 50  0001 C CNN
F 3 "~" H 4850 3150 50  0001 C CNN
	1    4850 3150
	1    0    0    1   
$EndComp
Wire Wire Line
	5150 3350 5500 3350
Wire Wire Line
	5150 3250 5500 3250
Wire Wire Line
	5150 3150 5500 3150
Wire Wire Line
	5150 3050 5500 3050
Wire Wire Line
	5150 2950 5500 2950
Text Label 5500 3350 2    50   ~ 0
PIN_10
Text Label 5500 3250 2    50   ~ 0
PIN_9
Text Label 5500 3150 2    50   ~ 0
PIN_8
Text Label 5500 3050 2    50   ~ 0
PIN_7
Text Label 5500 2950 2    50   ~ 0
PIN_6
Text Notes 6650 3600 0    50   ~ 0
SL 2X10G SMD2,54
Text Label 4200 2950 0    50   ~ 0
PIN_5
Text Label 4200 3050 0    50   ~ 0
PIN_4
Text Label 4200 3150 0    50   ~ 0
PIN_3
Text Label 4200 3250 0    50   ~ 0
PIN_2
Text Label 4200 3350 0    50   ~ 0
PIN_1
Wire Wire Line
	4650 2950 4200 2950
Wire Wire Line
	4650 3050 4200 3050
Wire Wire Line
	4650 3150 4200 3150
Wire Wire Line
	4650 3250 4200 3250
Wire Wire Line
	4650 3350 4200 3350
Text Notes 4100 3350 0    50   ~ 0
G
Text Notes 4050 3250 0    50   ~ 0
DP
Text Notes 4100 3150 0    50   ~ 0
A
Text Notes 4100 3050 0    50   ~ 0
F
Text Notes 3950 2950 0    50   ~ 0
Dig 2
Text Notes 5550 2950 0    50   ~ 0
D
Text Notes 5550 3050 0    50   ~ 0
E
Text Notes 5550 3150 0    50   ~ 0
C
Text Notes 5550 3250 0    50   ~ 0
B
Text Notes 5550 3350 0    50   ~ 0
Dig 1
$EndSCHEMATC
