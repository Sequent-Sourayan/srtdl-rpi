#include "analog.h"
#include "board.h"
#include "calib.h"
#include "cli.h"
#include "comm.h"
#include "help.h"
#include "led.h"
#include "misc.h"
#include "rtc.h"
#include "rtd.h"
#include "wdt.h"

const CliCmdType *gCmdArray[] = {
	&CMD_HELP,
	&CMD_VERSION,
	&CMD_BOARD,
	&CMD_CAL_STATUS,
	&CMD_WIND_DIR_READ,
	&CMD_WIND_SPEED_READ,
	&CMD_PANEL_VOLT_READ,
	&CMD_PANEL_CRT_READ,
	&CMD_FAN_PWR_READ,
	&CMD_FAN_PWR_WRITE,
	&CMD_PRESSURE_READ,
	&CMD_TEMP_READ,
	&CMD_U5_IN_READ,
	&CMD_U5_IN_CAL,
	&CMD_U30M_IN_READ,
	&CMD_U30M_IN_CAL,
	&CMD_I_IN_READ,
	&CMD_I_IN_CAL,
	&CMD_RTD_TEMP_READ,
	&CMD_RTD_RES_READ,
	&CMD_RTD_RES_CALIB,
	&CMD_RTC_GET,
	&CMD_RTC_SET,
	&CMD_WDT_RELOAD,
	&CMD_WDT_GET_PERIOD,
	&CMD_WDT_SET_PERIOD,
	&CMD_WDT_GET_INIT_PERIOD,
	&CMD_WDT_SET_INIT_PERIOD,
	&CMD_WDT_GET_OFF_PERIOD,
	&CMD_WDT_SET_OFF_PERIOD,
	&CMD_WDT_GET_RESET_COUNT,
	&CMD_WDT_CLR_RESET_COUNT,
	&CMD_LED_READ,
	&CMD_LED_WRITE,
	0
};
