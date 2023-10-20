#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "comm.h"
#include "data.h"
#include "rtc.h"

// TODO: debug cuz not working

const CliCmdType CMD_RTC_GET = {
	"rtcrd",
	1,
	&doRTCGet,
	"  rtcrd            Get the internal RTC date and time(mm/dd/yy hh:mm:ss)\n",
	"  Usage:           "PROGRAM_NAME" rtcrd \n",
	"  Example:         "PROGRAM_NAME" rtcrd; Get the nternal RTC time and date on Board #0\n"
};
int doRTCGet(int argc, char *argv[]) {
	(void)argv;
	if(argc != 2) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	uint8_t buff[6];
	if(OK != i2cMem8Read(dev, I2C_RTC_YEAR_ADD, buff, 6)) {
		printf("Fail to read RTC!\n");
		return ERR;
	}
	printf("%02u/%02u/%02u %02u:%02u:%02u\n",
			buff[1], buff[2], buff[0],
			buff[3], buff[4], buff[5]
	      );
	return OK;
}

const CliCmdType CMD_RTC_SET = {
	"rtcwr",
	1,
	&doRTCSet,
	"  rtcwr            Set the internal RTC date and time(mm/dd/yy hh:mm:ss)\n",
	"  Usage:           "PROGRAM_NAME" rtcwr <mm> <dd> <yy> <hh> <mm> <ss> \n",
	"  Example:         "PROGRAM_NAME" rtcwr 9 15 20 21 43 15; Set the internal RTC time and date on Board #0 at Sept/15/2020  21:43:15\n"
};
int doRTCSet(int argc, char *argv[]) {
	if(argc != 8) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERR;
	}
	int i;
	uint8_t buf[7];
	i = atoi(argv[2]);
	if(i < 1 || i > 12) {
		printf("Invalid month!\n");
		return ERR;
	}
	buf[1] = i;
	i = atoi(argv[3]);
	if(i < 1 || i > 31) {
		printf("Invalid date!\n");
		return ERR;
	}
	buf[2] = i;
	i = atoi(argv[4]);
	if(i < 0 || i > 99) {
		printf("Invalid year!\n");
		return ERR;
	}
	buf[0] = i;
	i = atoi(argv[5]);
	if(i < 0 || i > 23) {
		printf("Invalid hour!\n");
		return ERR;
	}
	buf[3] = i;
	i = atoi(argv[6]);
	if(i < 0 || i > 59) {
		printf("Invalid minute!\n");
		return ERR;
	}
	buf[4] = i;
	i = atoi(argv[7]);
	if(i < 0 || i > 59) {
		printf("Invalid second!\n");
		return ERR;
	}
	buf[5] = i;
	buf[6] = CALIBRATION_KEY;
	if(OK != i2cMem8Write(dev, I2C_RTC_SET_YEAR_ADD, buf, 7)) {
		printf("Fail to write RTC!\n");
		return ERR;
	}

	printf("done\n");
	return OK;
}
