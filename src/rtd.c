#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "calib.h"
#include "cli.h"
#include "comm.h"
#include "data.h"
#include "rtd.h"

const CliCmdType CMD_RTD_TEMP_READ = {
        "rtdrd",
        1,
        &doRtdTempRead,
        "  rtdrd            Display rtd temperature(C)\n",
        "  Usage:           "PROGRAM_NAME" rtdrd <channel>\n",
        "  Example:         "PROGRAM_NAME" rtdrd 1  Display rtd termperature on channel #1 on board #0 \n"
};
int doRtdTempRead(int argc, char *argv[]) {
        (void)argv;
        if(argc != 3) {
                return ARG_CNT_ERR;
        }
        int ch = atoi(argv[2]);
        if(!(MIN_CH_NO <= ch && ch <= RTD_CH_NO)) {
                return ARG_RANGE_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERR;
        }
        uint8_t buf[4];
        if(OK != i2cMem8Read(dev, I2C_MEM_RTD_TEMP1 + RTD_TEMP_DATA_SIZE * (ch - 1), buf, RTD_TEMP_DATA_SIZE)) {
		printf("Failed to read rtd temperature");
		return ERR;
        }
        float val;
        memcpy(&val, buf, RTD_TEMP_DATA_SIZE);
        printf("%.3f\n", val);
        return OK;
}

const CliCmdType CMD_RTD_RES_READ = {
        "rtdresrd",
        1,
        &doRtdResRead,
        "  rtdresrd         Display rtd resistance(ohm)\n",
        "  Usage:           "PROGRAM_NAME" rtdresrd <channel>\n",
        "  Example:         "PROGRAM_NAME" rtdresrd 1  Display rtd resistance on channel #1 on board #0 \n"
};
int doRtdResRead(int argc, char *argv[]) {
        (void)argv;
        if(argc != 3) {
                return ARG_CNT_ERR;
        }
        int ch = atoi(argv[2]);
        if(!(MIN_CH_NO <= ch && ch <= RTD_CH_NO)) {
                return ARG_RANGE_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERR;
        }
        uint8_t buf[4];
        if(OK != i2cMem8Read(dev, I2C_MEM_RTD_RES1 + RTD_RES_DATA_SIZE * (ch - 1), buf, RTD_RES_DATA_SIZE)) {
		printf("Failed to read rtd resistance");
		return ERR;
        }
        float val;
        memcpy(&val, buf, RTD_RES_DATA_SIZE);
        printf("%.3f\n", val);
        return OK;
}

const CliCmdType CMD_RTD_RES_CALIB = {
        "rtdcal",
        1,
        &doRtdResCal,
        "  rtdcal           Calibrate resistance measurement, the calibraion must be done in 2 points\n",
        "  Usage 1:         "PROGRAM_NAME" rtdcal <channel> <value(ohm)>\n"
        "  Usage 2:         "PROGRAM_NAME" rtdcal <channel> reset\n",
        "  Example:         "PROGRAM_NAME" rtdcal 1 100.34; Send one point of calibration at 100.34 ohm for channel #2\n"
};
int doRtdResCal(int argc, char *argv[]) {
        if(argc != 4) {
                return ARG_CNT_ERR;
        }
        int ch = atoi(argv[2]);
        if(!(MIN_CH_NO <= ch && ch <= RTD_CH_NO)) {
                return ARG_RANGE_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERR;
        }
	if(strcasecmp(argv[3], "reset") == 0) {
		if(OK != calibReset(dev, CAL_CH_RTD_RES_IN1 + (ch - 1))) {
			printf("Failed to reset calibration");
			return ERR;
		}
		return OK;
	}
	float val = atof(argv[3]);
	if(OK != calibSet(dev, CAL_CH_RTD_RES_IN1 + (ch - 1), val)) {
		printf("Failed to read rtd resistance");
		return ERR;
        }
        return OK;
}
