#ifndef PinDefintions_h
#define PinDefintions_h

////#include "mraa/common.hpp"

//General IO
/* https ://wiki.radxa.com/Rockpi4/dev/libmraa */
#define GPIO2_A2 3
#define GPIO2_B0 5
#define GPIO2_B3 7
#define GPIO4_C4 8
#define GPIO4_C3 10
#define GPIO4_C2 11
#define GPIO4_A3 12
#define GPIO4_C6 13
#define GPIO4_C5 15
#define GPIO4_D2 16
#define GPIO4_D4 18
#define GPIO1_B0 19
#define GPIO1_A7 21
#define GPIO4_D5 22
#define GPIO1_B1 23
#define GPIO1_B2 24
#define GPIO2_A0 27
#define GPIO2_A1 28
#define GPIO2_B2 29
#define GPIO2_B1 31
#define GPIO3_C0 32
#define GPIO2_B4 33
#define GPIO4_A5 35
#define GPIO4_A4 36
#define GPIO4_D6 37
#define GPIO4_A6 38
#define GPIO4_A7 40

//I2C
#define I2C7_SDA 3
#define I2C7_SCL 5
#define I2C2_SCL 27
#define I2C2_SCL_Alt 29
#define I2C6_SCL 29
#define I2C6_SDA 31

//2 SPI
#define SPI1TX 19 //must disable uart4
#define SPI1RX 21 //must disable uart4
#define SPI1_CLK 23
#define SPI1_CS 24
#define SPI2TX 29 //must disable i2c6
#define SPI2RX 31 //must disable i2c6
#define SPI2_CLK 7
#define SPI2_CS 33

//1 UART
#define UART2_TX 8
#define UART2_RX 10
#define UART4_TX 19
#define UART4_RX 21

//2 PWM
#define PWM0 11
#define PWM1 13

//1 ADC
#define ADC0 13 //the measure voltage must lower than 1.8v


//pinmodes


#endif // !PinDefintions_h

//Note Other Pins:
//3v3 = 1,17,
//5v = 2,4
//Ground = 6,9,14,20,25,30,34,39


//Mraa usefull info

///*gpio modes */
//#define G_MODE_STRONG "mode_strong"
//#define G_MODE_PULLUP "mode_pullup"
//#define G_MODE_PULLDOWN "mode_pulldown"
//#define G_MODE_HIZ "mode_hiz"
//#define G_MODE_ACTIVE_LOW "mode_active_low"
//#define G_MODE_OPEN_DRAIN "mode_open_drain"
//#define G_MODE_OPEN_SOURCE "mode_open_source"
//
///*gpio direction modes */
//#define G_DIR_OUT "out"
//#define G_DIR_IN "in"
//#define G_DIR_OUT_HIGH "out_high"
//#define G_DIR_OUT_LOW "out_low"
//
///*gpio edge modes */
//#define G_EDGE_NONE "edge_none"
//#define G_EDGE_BOTH "edge_both"
//#define G_EDGE_RISING "edge_rising"
//#define G_EDGE_FALLING "edge_falling"
//
///*gpio input modes */
//#define G_INPUT_ACTIVE_HIGH "input_high"
//#define G_INPUT_ACTIVE_LOW "input_low"
//
///*gpio output driver modes */
//#define G_OUTPUT_OPEN_DRAIN "output_open_drain"
//#define G_OUTPUT_PUSH_PULL "output_push_pull"
///*---------------------------------------------*/
//
///* i2c modes */
//#define I_MODE_STD "std"
//#define I_MODE_FAST "fast"
//#define I_MODE_HIGH "high"
///*---------------------------------------------*/
//
///* spi modes */
//#define S_MODE_0 "mode0"
//#define S_MODE_1 "mode1"
//#define S_MODE_2 "mode2"
//#define S_MODE_3 "mode3"
///*---------------------------------------------*/
//
///* uart parity types */
//#define U_PARITY_NONE "N"
//#define U_PARITY_EVEN "E"
//#define U_PARITY_ODD "O"
//#define U_PARITY_MARK "M"
//#define U_PARITY_SPACE "S"
///*---------------------------------------------*/

