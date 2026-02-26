#ifndef DATA_H
#define DATA_H

#include "type.h"

#define PROGRAM_NAME "srtdl"
#define CARD_NAME "strdl"
#define VERSION "1.0.1"
#define SLAVE_OWN_ADDRESS_BASE 0x51
#define SLAVE_SENSOR_ADDRESS 0x10
#define SENSOR_NAME "ATRH Sensor"

#define MV_TO_V ((float)0.001)
#define UV_TO_MV MV_TO_V
#define UA_TO_MA MV_TO_V

#define UI_VAL_SIZE 2
#define RTD_VAL_SIZE 4
#define PRES_TEMP_SIZE 4
#define RAIN_COUNT_SIZE 4

#define MIN_CH_NO 1
#define U5_IN_CH_NO 4
#define U30M_IN_CH_NO 4
#define I4_20_IN_CH_NO 4

#define RTD_CH_NO 4
#define RTD_TEMP_DATA_SIZE 4
#define RTD_RES_DATA_SIZE 4
#define PANEL_CH_NO 2
#define LED_CH_NO 4
#define ANALOG_VAL_SIZE 2

#define CALIBRATION_KEY 0xaa
#define RESET_CALIBRATION_KEY	0x55
#define CRT_MEASURE_CMD 0xaa
#define WDT_RESET_SIGNATURE     0xca
#define WDT_RESET_COUNT_SIGNATURE    0xbe

#define FLOAT_SIZE sizeof(float)


enum {
	CALIB_IN_PROGRESS = 0,
	CALIB_DONE,
	CALIB_ERR,
};

enum {
	I2C_MEM_SELECT_VAL = 0,//select type of input for universal channels 0 => 0..5V ; 1 => 0..30mV
	I2C_MEM_SELECT_30MV, // select input 0..30mV for specified channel
	I2C_MEM_SELECT_5V, // select input 0..5V for specified channel
	I2C_MEM_LEDS, // led's bitmap
	I2C_MEM_LED_SET,
	I2C_MEM_LED_CLR,
	I2C_MEM_RAIN_COUNT, // uint32_t unsigned integer for rain sensor counter
	I2C_MEM_RAIN_COUNT_RESET = I2C_MEM_RAIN_COUNT + RAIN_COUNT_SIZE, // reset command for rain counter (write RESET_CALIBRATION_KEY to reset the counter)
	I2C_MEM_WIND_DIR, // wind direction uint16_t express in mV [0..3300]
	I2C_MEM_WIND_SPEED = I2C_MEM_WIND_DIR + UI_VAL_SIZE, //uint16_t wind speed express in pulse per second
	I2C_MEM_I4_20MA_IN1 = I2C_MEM_WIND_SPEED + UI_VAL_SIZE,// uint16_t 4-20mA input 4xchannels expressed in uA [0..20000]
	I2C_MEM_U5V_IN1 = I2C_MEM_I4_20MA_IN1 + UI_VAL_SIZE * I4_20_IN_CH_NO, //uint16_t 0-5V input 4 x channels expressed in mV [0..50000]
	I2C_MEM_U30MV_IN1 = I2C_MEM_U5V_IN1 + UI_VAL_SIZE * U5_IN_CH_NO,//uint16_t 0-30mV input 4 x channels expressed in uV [0..30000]
	I2C_MEM_RTD_TEMP1 = I2C_MEM_U30MV_IN1 + UI_VAL_SIZE * U30M_IN_CH_NO,// float RTD temperature 4 X ch expressed in ohms
	I2C_MEM_RTD_RES1 = I2C_MEM_RTD_TEMP1 + RTD_VAL_SIZE * RTD_CH_NO, // float RTD resistance 4 X ch expressed in degree celsius
	I2C_MEM_PANEL_CMD = I2C_MEM_RTD_RES1 + RTD_VAL_SIZE * RTD_CH_NO, // Measure short circuit current command for both solar panels 0xaa -> initiate the measurement
	I2C_MEM_PANEL_VOLT1, //uint16_t solar panel voltage 2 x ch, expressed in mV
	I2C_MEM_PANEL_CRT1 = I2C_MEM_PANEL_VOLT1 + PANEL_CH_NO * UI_VAL_SIZE,//uint16_t solar panel short circuit current 2 x ch, expressed in mA
	I2C_MEM_FAN_PWR = I2C_MEM_PANEL_CRT1 + PANEL_CH_NO * UI_VAL_SIZE, // fan power set, single byte 0..100
	I2C_MEM_INT_PRESSURE, // float internal sensor pressure expressed in millibars
	I2C_MEM_INT_TEMPERATURE = I2C_MEM_INT_PRESSURE + PRES_TEMP_SIZE, //float internal sensor temperature
	I2C_MEM_CALIB_VALUE  = I2C_MEM_INT_TEMPERATURE + PRES_TEMP_SIZE,// reserve 4 bytes to accomodate both analog in and RTD
	I2C_MEM_CALIB_CHANNEL = I2C_MEM_CALIB_VALUE + 4, // calibration channels
	I2C_MEM_CALIB_KEY, //set calib point 0xaa; reset calibration on the channel 0x55
	I2C_MEM_CALIB_STATUS,
	I2C_RTC_YEAR_ADD,
	I2C_RTC_MONTH_ADD,
	I2C_RTC_DAY_ADD,
	I2C_RTC_HOUR_ADD,
	I2C_RTC_MINUTE_ADD,
	I2C_RTC_SECOND_ADD,
	I2C_RTC_SET_YEAR_ADD,
	I2C_RTC_SET_MONTH_ADD,
	I2C_RTC_SET_DAY_ADD,
	I2C_RTC_SET_HOUR_ADD,
	I2C_RTC_SET_MINUTE_ADD,
	I2C_RTC_SET_SECOND_ADD,
	I2C_RTC_CMD_ADD,
	I2C_MEM_WDT_RESET_ADD,
	I2C_MEM_WDT_INTERVAL_SET_ADD,
	I2C_MEM_WDT_INTERVAL_GET_ADD = I2C_MEM_WDT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_SET_ADD = I2C_MEM_WDT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_GET_ADD = I2C_MEM_WDT_INIT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_RESET_COUNT_ADD = I2C_MEM_WDT_INIT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_CLEAR_RESET_COUNT_ADD = I2C_MEM_WDT_RESET_COUNT_ADD + 2,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD = I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD
		+ 4,
	I2C_MEM_DIAG_TEMPERATURE = I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD + 4,
	I2C_MEM_DIAG_32V,
	I2C_MEM_DIAG_32V_1,
	I2C_MEM_DIAG_5V,
	I2C_MEM_DIAG_5V_1,
	I2C_MEM_DIAG_3V,
	I2C_MEM_DIAG_3V_1,
	I2C_MEM_CPU_RESET = 0xaa,
	I2C_MEM_REVISION_MAJOR = 253,
	I2C_MEM_REVISION_MINOR,
	SLAVE_BUFF_SIZE = 255
};

enum SENSOR_ADDRESSES {
	I2C_MEM_PRESSURE_ADD = 0,
	I2C_MEM_TEMPERATURE_ADD = I2C_MEM_PRESSURE_ADD + FLOAT_SIZE,
	I2C_MEM_DENSITY_ADD = I2C_MEM_TEMPERATURE_ADD + FLOAT_SIZE,
	I2C_MEM_HUMIDITY_ADD = I2C_MEM_DENSITY_ADD + FLOAT_SIZE,
	I2C_MEM_SECONDARY_TEMPERATURE_ADD = I2C_MEM_HUMIDITY_ADD + FLOAT_SIZE,
};

enum CALIB_CHANNELS{
	CAL_CH_NONE = 0,
	CAL_CH_I_IN1, // 4-20mA IN
	CAL_CH_I_IN2,
	CAL_CH_I_IN3,
	CAL_CH_I_IN4,
	CAL_CH_5V_IN1,// 0-5V IN
	CAL_CH_5V_IN2,
	CAL_CH_5V_IN3,
	CAL_CH_5V_IN4,
	CAL_CH_30MV_IN1,// 0-30mV IN
	CAL_CH_30MV_IN2,
	CAL_CH_30MV_IN3,
	CAL_CH_30MV_IN4,
	CAL_CH_WIND_DIR_IN,//wind direction in (0..3.3V)
	CAL_CH_SOL_V1,// solar panel voltage
	CAL_CH_SOL_V2,
	CAL_CH_RTD_RES_IN1,// RTD resistance
	CAL_CH_RTD_RES_IN2,
	CAL_CH_RTD_RES_IN3,
	CAL_CH_RTD_RES_IN4,
#ifdef SOLAR_PANEL_CRT_CAL //solar panel current calibration not implemented
	CAL_CH_SOL_I1,
	CAL_CH_SOL_I2,
#endif
	CAL_CH_NO
};

#define OK 0
#define ERR -1
#define ARG_CNT_ERR -2
#define ARG_RANGE_ERR -3

#define STR_(x) #x
#define STR(x) STR_(x)
#define MASK_1 1
#define MASK_2 3
#define MASK_3 7
#define MASK_4 15
#define MASK_5 31
#define MASK_6 63
#define MASK_7 127
#define MASK_(x) MASK_##x
#define MASK(x) MASK_(x)


#endif /* INC_DATA_H_ */
