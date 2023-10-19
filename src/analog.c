#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analog.h"
#include "calib.h"
#include "comm.h"
#include "data.h"

int val16Get(int dev, int baseAddr, int ch, float scale, float* val) {
	int addr = baseAddr + ANALOG_VAL_SIZE * (ch - 1);
	// TODO: check if addr in I2C_MEM_SIZE
	uint8_t buf[ANALOG_VAL_SIZE];
	if(OK != i2cMem8Read(dev, addr, buf, ANALOG_VAL_SIZE)) {
		return ERR;
	}
	int16_t raw = 0;
	memcpy(&raw, buf, ANALOG_VAL_SIZE);
	*val = (float)raw / scale;
	return OK;
}
int val16Set(int dev, int baseAddr, int ch, float scale, float val) {
	int addr = baseAddr + ANALOG_VAL_SIZE * (ch - 1);
	// TODO: check if addr in I2C_MEM_SIZE
	uint8_t buf[ANALOG_VAL_SIZE];
	int16_t raw = ceil(val * scale);
	memcpy(buf, &raw, 2);
	if(OK != i2cMem8Write(dev, addr, buf, ANALOG_VAL_SIZE)) {
		return ERR;
	}
	return OK;
}

const CliCmdType CMD_U_RES_WRITE = {/*{{{*/
	"ureswr",
	1,
	&doUResWrite,
	"  iinrd            Select resolution for voltage input\n",
	"  Usage 1:         "PROGRAM_NAME" iinrd <channel> <(0 0..5V/1 0..30mV)>\n"
	"  Usage 2:         "PROGRAM_NAME" iinrd <mask[1.."STR(MASK(U5_IN_CH_NO))">\n",
	"  Example:         "PROGRAM_NAME" iinrd 2 1 #Select 0..30mV for channel #2\n",
};
int doUResWrite(int argc, char *argv[]) {
	if(argc != 3 && argc != 4) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	if(argc == 3) {
		int val = atoi(argv[2]);
		if(!(0 <= val && val <= (1 << (U5_IN_CH_NO - 1)))) {
			printf("Mask value out of range[1..%d]", 1 << U5_IN_CH_NO);
			return ARG_RANGE_ERR;
		}
		u8 buf[1];
		memcpy(buf, &val, 1);
		if(OK != i2cMem8Write(dev, I2C_MEM_SELECT_VAL, buf, 1)) {
			printf("Fail to select resolution for channels\n");
			return ERR;
		}
	} else if(argc == 4) {
		u8 ch = atoi(argv[2]);
		if(!(1 <= ch && ch <= U5_IN_CH_NO)) {
			printf("Channel number out of range\n");
			return ARG_RANGE_ERR;
		}
		u8 val = atoi(argv[3]);
		u8 buf[sizeof(val)];
		u8 MEM;
		if(val == 0) {
			MEM = I2C_MEM_SELECT_5V;
		} else if(val == 1) {
			MEM = I2C_MEM_SELECT_30MV;
		} else {
			printf("Invalid value[0 or 1]\n");
			return ARG_RANGE_ERR;
		}
		if(OK != i2cMem8Write(dev, MEM, buf, sizeof(ch))) {
			printf("Fail to select resolution for channel %d", ch);
			return ERR;
		}
	}
	return OK;
}/*}}}*/

const CliCmdType CMD_U5_IN_READ = {/*{{{*/
	"u5inrd",
	1,
	&doU5InRead,
	"  u5inrd           Read 0-5V input voltage value(V)\n",
	"  Usage:           "PROGRAM_NAME" u5inrd <channel>\n",
	"  Example:         "PROGRAM_NAME" u5inrd 2 #Read voltage on 0-5V input channel #2\n",
};
int doU5InRead(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	int ch = atoi(argv[2]);
	if(!(1 <= ch && ch <= U5_IN_CH_NO)) {
		printf("0-5V channel out of range[1..%d]", U5_IN_CH_NO);
		return ARG_CNT_ERR;
	}
	u16 val;
	u8 buf[sizeof(val)];
	if(OK != i2cMem8Read(dev, I2C_MEM_U5V_IN1 + (ch - 1) * sizeof(val), buf, sizeof(val))) {
		printf("Fail to read 0-5V input channel voltage\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof(val));
	float fval = (float)val / 1000;
	printf("%.3f", fval);
	return OK;
}/*}}}*/
const CliCmdType CMD_U5_IN_CAL = {/*{{{*/
	"u5incal",
	1,
	&doU5Cal,
	"  u5incal          Calibrate 0-5V input channel\n",
	"  Usage 1:         "PROGRAM_NAME" u5incal <channel> <value(V)>\n"
	"  Usage 2:         "PROGRAM_NAME" u5incal <channel> reset\n",
	"  Example:         "PROGRAM_NAME" u5incal 1 4.81; Calibrate 0-5V input channel #1 at 4.81V\n"
};
int doU5Cal(int argc, char *argv[]) {
	if(argc != 4) {
		return ARG_CNT_ERR;
	}
	int ch = atoi(argv[3]);
	if(!(1 <= ch && ch <= I4_20_IN_CH_NO)) {
		return ARG_RANGE_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	if(strcasecmp(argv[3], "reset") == 0) {
		if(OK != calibReset(dev, CAL_CH_5V_IN1 + (ch - 1))) {
			return ERR;
		}
		return OK;
	}
	float value = atof(argv[3]);
	if(OK != calibSet(dev, CAL_CH_5V_IN1 + (ch - 1), value)) {
		return ERR;
	}
	return OK;
}/*}}}*/

const CliCmdType CMD_U30M_IN_READ = {/*{{{*/
	"u30inrd",
	1,
	&doU30MInRead,
	"  u5inrd           Read 0-30mV input voltage value(mV)\n",
	"  Usage:           "PROGRAM_NAME" u5inrd <channel>\n",
	"  Example:         "PROGRAM_NAME" u5inrd 2 #Read voltage on 0-30mV input channel #2\n",
};
int doU30MInRead(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	int ch = atoi(argv[2]);
	if(!(1 <= ch && ch <= U30M_IN_CH_NO)) {
		printf("0-30mV channel out of range[1..%d]", U30M_IN_CH_NO);
		return ARG_CNT_ERR;
	}
	u16 val;
	u8 buf[sizeof(val)];
	if(OK != i2cMem8Read(dev, I2C_MEM_U30MV_IN1 + (ch - 1) * sizeof(val), buf, sizeof(val))) {
		printf("Fail to read 0-30mV input channel voltage\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof(val));
	float fval = (float)val / 1000;
	printf("%.3f", fval);
	return OK;
}/*}}}*/
const CliCmdType CMD_U30M_IN_CAL = {/*{{{*/
	"u30incal",
	1,
	&doU30Cal,
	"  u30incal         Calibrate 0-30mV input channel\n",
	"  Usage 1:         "PROGRAM_NAME" u30incal <channel> <value(mV)>\n"
	"  Usage 2:         "PROGRAM_NAME" u30incal <channel> reset\n",
	"  Example:         "PROGRAM_NAME" u30incal 1 28.43; Calibrate the 0-30mV input channel #1 at 28.43mV\n"
};
int doU30Cal(int argc, char *argv[]) {
	if(argc != 4) {
		return ARG_CNT_ERR;
	}
	int ch = atoi(argv[3]);
	if(!(1 <= ch && ch <= I4_20_IN_CH_NO)) {
		return ARG_RANGE_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	if(strcasecmp(argv[3], "reset") == 0) {
		if(OK != calibReset(dev, CAL_CH_30MV_IN1 + (ch - 1))) {
			return ERR;
		}
		return OK;
	}
	float value = atof(argv[3]);
	if(OK != calibSet(dev, CAL_CH_30MV_IN1 + (ch - 1), value)) {
		return ERR;
	}
	return OK;
}/*}}}*/

const CliCmdType CMD_I_IN_READ = {/*{{{*/
	"iinrd",
	1,
	&doIInRead,
	"  iinrd            Read 4-20mA input amperage value(mA)\n",
	"  Usage:           "PROGRAM_NAME" iinrd <channel>\n",
	"  Example:         "PROGRAM_NAME" iinrd 2 #Read amperage on 4-20mA input channel #2 on board #0\n",
};
int doIInRead(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int ch = atoi(argv[2]);
	if(!(1 <= ch && ch <= I4_20_IN_CH_NO)) {
		return ARG_RANGE_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	u16 val;
	u8 buf[sizeof(val)];
	if(OK != i2cMem8Read(dev, I2C_MEM_I4_20MA_IN1 + (ch - 1) * sizeof(val), buf, sizeof(val))) {
		printf("Fail to read 4-20mA input channel amperage\n");
		return ERR;
	}
	memcpy(&val, buf, sizeof(val));
	float fval = (float)val / 1000;
	printf("%.3f\n", fval);
	return OK;
}/*}}}*/

const CliCmdType CMD_I_IN_CAL = {/*{{{*/
	"iincal",
	1,
	&doIInCal,
	"  iincal           Calibrate 4-20mA input channel, the calibration must be done in 2 points at min 10mA apart\n",
	"  Usage 1:         "PROGRAM_NAME" iincal <channel> <value(A)>\n"
	"  Usage 2:         "PROGRAM_NAME" iincal <channel> reset\n",
	"  Example:         "PROGRAM_NAME" iincal 1 0.5; Calibrate the 4-20mA input channel #1 on board #0 at 0.5V\n"
};
int doIInCal(int argc, char *argv[]) {
	if(argc != 4) {
		return ARG_CNT_ERR;
	}
	int ch = atoi(argv[3]);
	if(!(1 <= ch && ch <= I4_20_IN_CH_NO)) {
		return ARG_RANGE_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	if(strcasecmp(argv[3], "reset") == 0) {
		if(OK != calibReset(dev, CAL_CH_I_IN1 + (ch - 1))) {
			return ERR;
		}
		return OK;
	}
	float value = atof(argv[3]);
	if(OK != calibSet(dev, CAL_CH_I_IN1 + (ch - 1), value)) {
		return ERR;
	}
	return OK;
}/*}}}*/

// vi:fdm=marker
